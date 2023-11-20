#include<iostream>
#include<map>
using namespace std;

//原始字面量    R"()"
void test() {
	string s = "D:\hello\world\test.txt";        //会将\t进行转义
	cout << s << endl;
	string s1 = "D:\\hello\\world\\test.txt";    //使用\\避免转义
	cout << s1 << endl;
	string s2 = R"(D:\hello\world\test.txt)";    //使用原始字面量避免转义   类似python中的r" "
	cout << s2 << endl;
	string s3 = "hello\
				 world\
				 C++\
				 Java";     //多行内容连接需要加\

	cout << s3 << endl;
	string s4 = R"(hello
				   world
				   C++
				   Java)";    //使用原始字面量就不需要加\

	cout << s4 << endl;

}

void function(int a) {
	cout << "void funcation(int a)被调用" << endl;
}

void function(char* a) {
	cout << "void funcation(char* a)被调用" << endl;
}

//指针空值类型    nullptr
void test1() {
	function(10);
	function(NULL);      //依然调用的是int a  因为NULL在C++中表示0
	function(nullptr);   //调用的是char* a

	char* p1 = nullptr;   //对于指针类型的初始化，建议使用nullptr代替NULL，这样代码更具有健壮性
	int* p2 = nullptr;
	double* p3 = nullptr;

}

//constexpr class T {    //报错，对于自定义数据类型，不能直接使用constexpr进行修饰，但是可以修饰其对象
class T{
public:
	int age;
	constexpr T() :age(200){     //constexpr修饰构造函数，函数体必须为空，如果要进行初始化，必须使用初始化列表

	}
};

constexpr int function1() {       //constexpr修饰函数，必须有返回值，并且返回值必须是常量表达式
	constexpr int c = 300;
	return c;
}

//constexpr修饰常量表达式    使用constexpr可以提高程序的运行效率，因为它的计算发生在程序编译的阶段
void test2() {
	constexpr int a = 100;         //对于内置数据类型可以直接使用constexpr进行修饰
	constexpr double b = 3.14;  
	//a = 200;                     //报错，值不可以进行修改
	constexpr T t;                 //constexpr修饰类对象
	//t.age = 200;                 //报错，值不可以进行修改
	cout << a << " " << b << " " << t.age << " " << function1() << endl;
}

class T1 {
public:
	static int get() {
		return 10;
	}
};

class T2 {
public:
	static  string get() {
		return "hello world";
	}
};

template<class T>
void function1(){
	auto i = T::get();     //自动类型推导，根据传入的类型自己去决定使用哪种类型，比显示指定方便
    cout << "result:" << i << endl;
}

//自动类型推导 auto
void test3() {
	auto x = 3.14;      //自动类型推导  double
	auto y = 10;        //int 
	auto z = 'a';       //char

	int temp = 110;
	auto x1 = &temp;    //int*
	auto* x2 = &temp;   //int
	auto x3 = temp;     //int

	const auto x4 = temp;   //int
	auto x5 = x4;           //虽然x4是const int,但是不是指针和引用，所以为int
	const auto& x6 = temp;  //int
	auto& x7 = x6;          //const int
	auto* x8 = &x4;         //const int      const int*  常量指针  指向的值不可以改，指向可以改  * const int  指针常量  指向不可以改，指向的值可以改
	//*x8 = 100;            //报错，值不可以改
	x8 = &x6;               //指向可以改

	//auto的使用场景   STL的遍历
	map<int, string> mp;
	mp.insert(make_pair(1, "zxc"));
	mp.insert(make_pair(2, "asd"));
	mp.insert(make_pair(3, "qwe"));
	//for (map<int, string>::iterator it = mp.begin(); it != mp.end(); it++) {
	//	cout << "key:" << (*it).first << " ,value:" << (*it).second << endl;
	//}
	for (auto it = mp.begin(); it != mp.end(); it++) {     //优化
		cout << "key:" << (*it).first << " ,value:" << (*it).second << endl;
	}

	//用于泛型编程
	function1<T1>();
	function1<T2>();

}

//int main() {
//	//test();
//	//test1();
//	//test2();
//	test3();
//
//	system("pause");
//	return 0;
//}