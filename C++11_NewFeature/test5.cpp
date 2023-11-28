#include<iostream>
#include<memory>
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
//智能指针
void test18() {
	//共享智能指针的初始化
	
	//通过构造函数进行初始化
	shared_ptr<int> ptr1(new int(3));
	cout << "ptr1.use_count = " << ptr1.use_count() << endl;
	cout << "-------------------------------------------" << endl;

	//通过移动构造函数和拷贝构造函数进行初始化
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
}

int main() {
	test18();
	system("pause");
	return 0;
}