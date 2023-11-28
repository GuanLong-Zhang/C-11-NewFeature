#include<iostream>
#include<functional>
#include<list>
using namespace std;

//可调用对象包装器 绑定器
//可调用对象
//函数指针
void print(int num, string name) {     //普通函数
	cout << "普通函数  num: " << num << "   name: " << name << endl;
}
using func = void(*)(int, string);   //函数指针

//仿函数   重载小括号
class Test {
public:
	int mid = 10;
public:
	void operator()(string name) {
		cout << "仿函数    name: " << name << endl;
	}

	//可以转换为函数指针的类对象
	operator func() {
		return world;
	}

	void hello(int num, string name) {              //没有被static修饰的成员函数，属于对象，不属于类
		cout << "hello函数 num: " << num << "   name: " << name << endl;
	}

	static void world(int num, string name) {       //static修饰成员函数，该函数属于类
		cout << "world函数 num: " << num << "   name: " << name << endl;
	}
};

class A {
public:
	A(const function<void(int, string)>& f) : callback(f) {

	}
	void notify(int num, string name) {
		callback(num, name);
	}
private:
	function<void(int, string)> callback;
};

void output(int x, int y) {
	cout << x << " " << y << endl;
}

void output_add(int x, int y) {
	cout << "x = " << x << " y = " << y << " x + y = " << x + y << endl;
}

void testFunc(int x, int y, const function<void(int, int)>&f) {
	if (x % 2 == 0) {
		f(x, y);
	}
}

class B {
public:
	void output_B(int x, int y) {
		cout << "x = " << x << " y = " << y << endl;
	}
	int num = 100;
};

void test12() {
	func f = print;                  //函数指针指向普通函数
	f(1, "zxc");

	Test t;
	t("zxc");                        //调用仿函数

	Test t1;
	t1(1, "zxc");                    //类对象转换为函数指针

	func f1 = Test::world;           //类成员函数指针   函数指针指向静态成员函数
	f1(1, "zxc");
	using func1 = void(Test::*)(int, string);   //重新定义函数指针，不过此时加入了类的作用域，所以可以访问非静态成员函数了
	func1 f2 = &Test::hello;

	using func2 = int Test::*;       //类成员变量指针
	func2 f3 = &Test::mid;

	Test t2;                         //对两个指针解引用，然后调用
	(t2.*f2)(1, "zxc");
	t2.*f3 = 100;
	cout << "mid = " << t2.mid << endl;
	cout << "---------------------------------" << endl;

	//可调用对象包装器
	//包装普通函数
	function<void(int, string)> f4 = print;
	f4(2, "asd");
	//包装类的静态成员函数
	function<void(int, string)> f5 = Test::world;
	f5(2, "asd");
	//包装仿函数
	Test t3;
	function<void(string)> f6 = t3;
	f6("asd");
	//包装转换为函数指针的类对象
	Test t4;
	function<void(int, string)> f7 = t4;
	f7(2, "asd");
	cout << "---------------------------------" << endl;

	A a1(print);                  //传入普通函数
	a1.notify(3, "qwe");

	A a2(Test::world);            //传入类的静态成员函数
	a2.notify(3, "qwe");

	//也可以传入仿函数，但是仿函数参数和notify参数类型不匹配，所以就没有进行测试

	A a4(t4);                     //传入转换为函数指针的类对象
	a4.notify(3, "qwe");
	cout << "---------------------------------" << endl;

	//可调用对象绑定器   
	//可绑定非类成员函数/变量，也可绑定类成员函数/变量
	//非类成员函数/变量
	bind(output, 1, 2)();                                        //1 2
	bind(output, placeholders::_1, 2)(1);                        //1 2     placeholders::_1 占位符
	bind(output, 1, placeholders::_1)(2);                        //1 2

	bind(output, 1, placeholders::_2)(10, 2);                    //1 2
	bind(output, placeholders::_1, placeholders::_2)(1, 2);      //1 2
	cout << "---------------------------------" << endl;

	for (int i = 0; i < 10; i++) {
		//auto f = bind(output_add, i + 100, i + 200);  //没有使用占位符，后续的指定没有意义
		//testFunc(i, i, f);
		auto f8 = bind(output_add, placeholders::_1 ,placeholders::_2);  //添加占位符，后续的操作才可以生效
		testFunc(i, i, f8);
	}
	cout << "---------------------------------" << endl;

	//类成员函数/变量
	B b;
	auto f9 = bind(&B::output_B, &b, 520, placeholders::_1);  //f9为一个仿函数
	f9(1314);
	//包装 + 绑定
	function<void(int, int)> f9_1 =  bind(&B::output_B, &b, placeholders::_1, placeholders::_2);
	f9_1(520, 1314);


	auto f10 = bind(&B::num, &b);                             //f10为一个仿函数
	cout << "num = " << f10() << endl;
	f10() = 200;
	cout << "num = " << f10() << endl;
	//包装 + 绑定
	function<int& (void)> f10_1 = bind(&B::num, &b);
	cout << "num = " << f10_1() << endl;
	f10_1() = 300;
	cout << "num = " << f10_1() << endl;

}

//lambda表达式
void assign(int x, int y) {
	int a = 1;
	int b = 2;
	[=, &x]() mutable{        //除x是按照引用捕获的，其余的都是值捕获   要修改只读数据，需要加mutable
		int c = a;
		int d = x;
		b++;
		cout << "b = " << b << endl;   //虽然值发生了变化，但是值拷贝，形参改变不影响实参,外部b不会发生改变
	}();        //调用需要加()
	cout << "b = " << b << endl;
}

class C {
public:
	void output(int x, int y) {
		auto x1 = [=]() {return number + x + y; }();     //按值捕获    只读
		auto x2 = [&]() {return number + x + y; }();     //按引用捕获
		auto x3 = [this]() {return number; }();          //捕获成员变量/函数
		auto x4 = [this, x, y]() {return number + x + y; }();  //捕获成员变量/函数 以及 x y 
		cout << "x1 = " << x1 << " x2 = " << x2 << " x3 = " << x3 << " x4 = " << x4 << endl;

	}
private:
	int number = 100;
};

void toPtr(int x, int y) {
	using ptr = void (*)(int);              //函数指针
	ptr p1 = [](int z0) {                   //空捕获，可以转换为一个函数指针
		cout << "z0 = " << z0 << endl;
	};
	p1(10);

	function<void(int)> f11 = [=](int z1) {        //lambda表达式本质是一个仿函数,使用包装器进行接收
		cout << "z1 = " << z1 << endl;
	};
	f11(20);

	function<void(int)> f12 = bind([=](int z2) {       //先使用绑定器进行绑定,然后使用包装器进行接收
		cout << "z2 = " << z2 << endl;
		}, placeholders::_1);
	f12(30);

}

void test13() {
	assign(3, 4);
	C c;
	c.output(1, 2);
	toPtr(100, 200);
}

//左值和左值引用 右值和右值引用
class D {
private:
	int* myNum;
public:
	D() : myNum(new int(100)) {
		cout << "无参构造函数被调用" << endl;
	}

	D(const D& d1) : myNum(new int(*d1.myNum)) {    //深拷贝
		cout << "拷贝构造函数被调用" << endl;
	}

	//移动构造函数  进行浅拷贝   复用堆内存空间
	D(D&& d1) : myNum(d1.myNum) {
		d1.myNum = nullptr;
		cout << "移动构造函数被调用" << endl;
	}

	~D() {
		cout << "析构函数被调用" << endl;
		delete myNum;
	}

};

D getObj() {
	D obj;
	return obj;    
}

D getObj1() {
	return D();
}

D&& getObj2() {
	return D();
}

void test14() {
	//左值num
	int num = 9;
	//左值引用    相当于给num起别名  左值引用a
	int& a = num;
	//右值 和 右值引用
	int&& b = 10;      //右值10，右值引用b  需要加&&
	//常量右值引用
	const int&& d = 100;
	//常量左值引用
	const int& c = num;   //左值初始化
	const int& c1 = a;    //左值引用初始化
	const int& c2 = b;    //右值引用初始化
	const int& c4 = d;    //常量右值引用初始化

	D obj;
	D obj1 = obj;    //创建对象的时候。将obj赋给obj1    调用拷贝构造函数
	D obj2 = move(obj);   //move强制将左值转换为右值，调用移动构造函数
	
	//D obj3 = getObj();   //getObj()为临时变量，返回的值为右值，但是却没有调用到移动构造函数
	//D &&obj4 = getObj1();
	//D&& obj5 = getObj2();
}

//未定义的引用类型的推导   
//并不是&&,a就是右值引用，需要根据传入的实参进行推导
//传入右值，则推导出的是右值引用；传入非右值，那么推导出为左值引用
template<typename T>
void funcT(T&& a) {
	cout << "模板函数被调用" << endl;
}

void test15() {
	funcT(10);     //传入右值，a为右值引用
	int xT = 10;   //xT为左值
	funcT(xT);     //传入左值，a为左值引用   传入实参是非右值，a均是左值引用

	//非右值包括：左值，左值引用，右值引用，常量左值引用，常量右值引用  

	auto&& aT = xT;    //传入左值，aT为左值引用
	auto&& aT1 = 250;  //传入右值，aT1为右值引用
	int&& v1 = 100;    //v1为右值引用
	auto&& v2 = v1;    //v2为左值引用，因为传入的参数是右值引用
	int& v3 = xT;      //v3为左值引用
	auto&& v4 = v3;    //v4为左值引用，因为传入的参数是左值引用
	const int& v5 = xT;    //v5为常量左值引用
	auto&& v6 = v5;        //v6为常量左值引用，因为传入的参数是常量左值引用 
	const int&& v7 = 300;  //v7为常量右值引用
	auto&& v8 = v7;        //v8为常量左值引用，因为传入的参数是常量右值引用   

}

//右值引用的传递
//右值引用在传递的时候，会把其转换为左值引用
void printValue(int&& a) {
	cout << "右值引用函数被调用a = " << a << endl;
}

void printValue(int& a) {
	cout << "左值引用函数被调用a = " <<a << endl;
}

void forward(int&& a) {   //int&& a表明a是一个右值，但是在传递的时候会将其转换为左值
	printValue(a);
}

void test16() {
	int va = 100;
	printValue(va);
	printValue(200);
	forward(300);
}

template<typename T>
void printKey(T& t) {
	cout << "左值引用函数被调用t = " << t << endl;
}

template<typename T>
void printKey(T&& t) {
	cout << "右值引用函数被调用t = " << t << endl;
}

template<typename T>
void testForward(T&& t) {     //自动类型推导，非右值，均为左值引用
	printKey(t);              //右值引用在传递的时候，会变成左值引用
	printKey(move(t));        //左值转右值
	printKey(forward<T>(t));   //当T为左值引用，t就为左值；当T为非左值引用，那么t就为右值
	cout << endl;

}

//转移和完美转发  move forward
void test17() {
	int Aa = 10;             //Aa为一个左值
	int&& Bb = move(Aa);     //直接使用左值给右值引用初始化会报错，所以使用move将左值转换为右值，进行右值引用的初始化

	list<string> l1 = { "hello","world","C++","Java" };
	list<string>l2 = move(l1);   //使用move进行资源转移，提高效率。  l1之后不会被使用，并且需要拷贝到l2,那么就可以使用move进行资源转移，提高效率

	testForward(520);    //左 右 右
	testForward(Aa);     //左 右 左
	testForward(forward<int>(Aa));   //左 右 右
	testForward(forward<int&>(Aa));  //左 右 左
	testForward(forward<int&&>(Aa)); //左 右 右
}


//int main() {
//	//test12();
//	//test13();
//	//test14();
//	//test15();
//	//test16();
//	test17();
//
//	system("pause");
//	return 0;
//}