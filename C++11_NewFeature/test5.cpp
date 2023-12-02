#include<iostream>
#include<memory>
#include<functional>
using namespace std;

class Test {
private:
	int num;
public:
	Test() {
		cout << "无参构造函数" << endl;
	}

	Test(int i) :num(i) {
		cout << "整型构造函数" << endl;
	}

	Test(string s){
		cout << "字符型构造函数" << endl;
	}

	~Test() {
		cout << "析构函数" << endl;
	}

	void setNum(int num) {
		this->num = num;
	}

	void printNum() {
		cout << "num = " << num << endl;
	}

};

//删除数组内存模板函数
template<typename T>
shared_ptr<T> make_share_array(size_t size) {
	return shared_ptr<T>(new T[size], default_delete<T[]>());
}

//智能指针
//共享智能指针
void test18() {
	//共享智能指针的初始化
	
	//通过构造函数进行初始化
	shared_ptr<int> ptr1(new int(3));
	cout << "ptr1.use_count = " << ptr1.use_count() << endl;
	cout << "-------------------------------------------" << endl;

	//通过移动构造函数和拷贝构造函数进行初始化    使用use_count()可以查看使用基数
	shared_ptr<int> ptr2 = move(ptr1);                           //进行了移动
	cout << "ptr1.use_count = " << ptr1.use_count() << endl;     //0
	cout << "ptr2.use_count = " << ptr2.use_count() << endl;     //1
	shared_ptr<int> ptr3 = ptr2;                                 //进行了拷贝
	cout << "ptr2.use_count = " << ptr2.use_count() << endl;     //2
	cout << "ptr3.use_count = " << ptr3.use_count() << endl;     //2
	cout << "-------------------------------------------" << endl;

	//通过make_shared进行初始化
	shared_ptr<int> ptr4 = make_shared<int>(4);
	shared_ptr<Test> ptr5 = make_shared<Test>();              //无参
	shared_ptr<Test> ptr6 = make_shared<Test>(5);             //整型
	shared_ptr<Test> ptr7 = make_shared<Test>("hello");       //字符型
	cout << "ptr4.use_count = " << ptr4.use_count() << endl;     //1
	cout << "ptr5.use_count = " << ptr5.use_count() << endl;     //1
	cout << "ptr6.use_count = " << ptr6.use_count() << endl;     //1
	cout << "ptr7.use_count = " << ptr7.use_count() << endl;     //1
	cout << "-------------------------------------------" << endl;

	//通过reset进行初始化
	ptr4.reset();                                                //重置指针
	cout << "ptr4.use_count = " << ptr4.use_count() << endl;     //0
	ptr4.reset(new int(6));                                      //重新指向新的内存空间
	cout << "ptr4.use_count = " << ptr4.use_count() << endl;     //1
	cout << "-------------------------------------------" << endl;

	//共享智能指针的使用

	//通过get获得原始地址，然后通过原始地址进行操作
	Test *t = ptr6.get();
	t->setNum(999);
	t->printNum();

	//通过共享智能指针对象直接进行操作
	ptr6->setNum(888);
	ptr6->printNum();
	cout << "-------------------------------------------" << endl;

	//删除器
	shared_ptr<Test>ptr8(new Test(666), [](Test* t) {cout << "删除器1被调用" << endl;  delete t; }); //删除器用lambda表达式来定义
	cout << "ptr8.use_count = " << ptr8.use_count() << endl;      //1
	   
	//对于数组内存，必须指定删除器
	//对于非数组内存，共享指针默认删除器就可以删除
	shared_ptr<Test>ptr9(new Test[5], [](Test* t) {cout << "删除器2被调用" << endl;  delete[]t; });
	cout << "ptr9.use_count = " << ptr9.use_count() << endl;      //1

	//默认删除器
	shared_ptr<Test>ptr10(new Test[5], default_delete<Test[]>());     //析构执行顺序，先调用的后析构
	cout << "ptr10.use_count = " << ptr10.use_count() << endl;    //1

	//删除数组内存模板函数
	shared_ptr<int> ptr11 = make_share_array<int>(10);    //int数组 大小为10;
	cout << "ptr11.use_count = " << ptr11.use_count() << endl;     //1
	shared_ptr<char> ptr12 = make_share_array<char>(10);  //char数组，大小为10
	cout << "ptr12.use_count = " << ptr12.use_count() << endl;     //1
}

unique_ptr<int>function1() {
	return unique_ptr<int>(new int(520));
}

//独占智能指针
void test19() {
	//独占智能指针初始化
	
	//通过构造函数进行初始化
	unique_ptr<int> ptr13(new int(10));
	
	//通过移动构造函数进行初始化
	unique_ptr<int> ptr14 = move(ptr13);
	unique_ptr<int> ptr15 = function1();

	//通过reset进行初始化
	ptr14.reset();                //重置指针
	ptr14.reset(new int(100));    //让指针指向新的内存空间

	//独占智能指针的使用
	
	//通过get获得原始地址，然后通过原始地址进行操作
	unique_ptr<Test> ptr16(new Test(666));
	Test* t = ptr16.get();
	t->setNum(1000);
	t->printNum();

	//通过独占智能指针对象直接进行操作
	ptr16->setNum(2000);
	ptr16->printNum();

	//删除器

	//和共享智能指针删除器有所区别，需要指明删除器的类型
	//没有捕获对象的lambda表达式可以被看成函数指针
	using ptrType = void(*)(Test*);      //using给函数指针起别名   
	unique_ptr<Test, ptrType> ptr17(new Test("hello"), [](Test* t) {cout << "删除器3被调用" << endl; delete t; });
	
	//有捕获对象的lambda表达式是一个仿函数,需要用包装器对其进行包装
	unique_ptr<Test, function<void(Test*)>> ptr18(new Test(100), [=](Test* t) {cout << "删除器4被调用" << endl; delete t; });

	//独占智能指针可以管理数组内存，能够自动释放，不需要像共享智能指针那样必须指定删除器
	unique_ptr<Test[]>ptr19(new Test[5]);

	//在C++11中，共享智能指针不能管理数组内存，但是在C++11之后就可以了
	shared_ptr<Test[]>ptr20(new Test[5]);
}

//弱引用智能指针   辅助共享智能指针工作的
void test20() {
	 //弱引用智能指针初始化
	shared_ptr<int> sp(new int);
	weak_ptr<int> wp;

	weak_ptr<int> wp1(sp);    //通过shared_ptr对象进行初始化    实例化
	weak_ptr<int> wp2(wp);    //通过weak_ptr对象进行初始化      未实例化

	weak_ptr<int> wp3;
	wp3 = sp;

	weak_ptr<int> wp4;
	wp4 = wp;

	//常用方法
	//use_count()   查看资源引用基数的
	cout << "sp = " << sp.use_count() << endl;       //1
	cout << "wp = " << wp.use_count() << endl;       //0    未实例化，所以引用基数为0
	cout << "wp1 = " << wp1.use_count() << endl;     //1
	cout << "wp2 = " << wp2.use_count() << endl;     //0    
	cout << "wp3 = " << wp3.use_count() << endl;     //1
	cout << "wp4 = " << wp4.use_count() << endl;     //0

	//expired()   查看资源是否被释放(即引用基数是否为0)    释放返回true
	cout << "wp " << (wp.expired() ? "is" : "is not") << " expired" << endl;
	cout << "wp1 " << (wp1.expired() ? "is" : "is not") << " expired" << endl;
	wp1.reset();      //重置指针
	cout << "wp1 " << (wp1.expired() ? "is" : "is not") << " expired" << endl;

	//lock()  得到所监测资源的shared_ptr对象    reset() 重置weak_ptr
	shared_ptr<int> sp1, sp2;
	weak_ptr<int> wpp;

	sp1 = make_shared<int>(520);
	wpp = sp1;
	sp2 = wpp.lock();
	cout << "wpp = " << wpp.use_count() << endl;
	
	sp1.reset(); 
	cout << "wpp = " << wpp.use_count() << endl;

	sp1 = wpp.lock();
	cout << "wpp = " << wpp.use_count() << endl;

}

class TE : public enable_shared_from_this<TE>{
public:
	shared_ptr<TE> getshared_ptr() {
		return shared_ptr<TE>(this);     //调用会报错
	}

	shared_ptr<TE> getshared_ptr_1() {
		return shared_from_this();      //this报错的解决方法
	}

	~TE() {
		cout << "析构函数被调用" << endl;
	}
};

class TA;
class TB;

class TA {
public:
	//shared_ptr<TB> bptr;
	weak_ptr<TB> bptr;        //解决智能指针循环引用问题，可以使用weak_ptr来代替shared_ptr
	~TA(){
		cout << "TA析构函数被调用" << endl;
	}
};

class TB {
public:
	shared_ptr<TA>aptr;
	~TB() {
		cout << "TB析构函数被调用" << endl;
	}
};


//shared_ptr的使用注意事项   3条
void test21() {
	//TE *te = new TE;
	//shared_ptr<TE>ptr1(te);      //不能使用同一个原始地址初始化多个shared_ptr   
	//cout << "ptr1 = " << ptr1.use_count() << endl;
	////shared_ptr<TE>ptr2(te);    //报错，同一块内存被两次析构
	//shared_ptr<TE> ptr2 = ptr1;  //拷贝构造函数进行初始化
	//cout << "ptr2 = " << ptr2.use_count() << endl;

	//shared_ptr<TE>ptr3(new TE);
	//cout << "ptr3 = " << ptr3.use_count() << endl;
	////shared_ptr<TE>ptr4 = ptr3->getshared_ptr();  //报错，getshared_ptr()包含this指针,那么就指向了同一个原始地址，同一块内存被两次析构
	//shared_ptr<TE>ptr4 = ptr3->getshared_ptr_1();  //解决方法  继承enable_shared_from_this<>,然后return shared_from_this()
	//cout << "ptr4 = " << ptr4.use_count() << endl;

	shared_ptr<TA> ptr5(new TA);
	shared_ptr<TB> ptr6(new TB);
	cout << "ptr5 = " << ptr5.use_count() << endl;   //1
	cout << "ptr6 = " << ptr6.use_count() << endl;   //1

	ptr5->bptr = ptr6;    //循环引用，shared_ptr无法释放，无法调用析构函数，造成内存泄漏
	ptr6->aptr = ptr5;
	cout << "ptr5 = " << ptr5.use_count() << endl;   //2
	cout << "ptr6 = " << ptr6.use_count() << endl;   //1
	//解决循环引用的方法就是使用weak_ptr，解除循环引用
}

int main() {
	//test18();
	//test19();
	//test20();
	test21();

	system("pause");
	return 0;
}