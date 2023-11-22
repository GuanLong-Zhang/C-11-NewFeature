#include<iostream>
#include<functional>
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
	
int main() {
	test12();


	system("pause");
	return 0;
}