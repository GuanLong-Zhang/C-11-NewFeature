#include<iostream>
#include<list>
#include<map>
using namespace std;

class T3 {
public:
	int num = 9;
	string txt;
	static const int value = 100;
};

//函数声明
int function2();
int& function3();
int&& function4();
const int function5();
const int& function6();
const int&& function7();
const T3 function8();

template<class T>
class container {
private:
	decltype(T().begin()) it;      //decltype进行迭代器自动类型推导    T()得到对象，然后T().begin()得到迭代器
public:
	void printContainer(T& t) {
		for (it = t.begin(); it != t.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
};

//自动类型推导 decltype
void test4() {
	int a = 1;
	decltype(a) b = 2;                 //int    
	decltype(a + 3.14) c = 3.1415;     //double
	const int& d = a;
	decltype(d) e = a;                 //const int&
	decltype(T3::value) f = a;         //const int
	T3 t0;
	decltype(t0.txt) g = "hello world";  //string

	decltype(function2()) h = 0;        //int
	decltype(function3()) i = h;        //int&
	decltype(function4()) j = 0;        //int&&
	decltype(function5()) k = 0;        //int   省略const   就此情况特殊
	decltype(function6()) l = h;        //const int &
	decltype(function7()) m = 0;        //const int &&
	decltype(function8()) n = T3();     //const T3

	const T3 t1;
	decltype(t1.num) o = 0;             //int
	decltype((t1.num)) p = o;           //const int &   被小括号包围，并且对象被const修饰
	int q = 0; 
	int s = 0;
	decltype(q + s) t = 0;              //int
	decltype(s = q + s) u = q;          //int &   表达式是一个左值，所以推导出是引用

	list<int> li = { 1, 2, 3, 4, 5, 6 };   //使用初始化列表进行赋值
	container<list<int>> con;
	con.printContainer(li);

	const list<int> li1 = { 1, 2, 3, 4, 5, 6 };   
	container<const list<int>> con1;
	con1.printContainer(li1);
}

template<typename T0, typename T1>
auto add(T0 t0, T1 t1) -> decltype(t0 + t1){
	return t0 + t1;
}

//返回类型后置   auto和decltype的混合使用
void test5() {
	int xx = 512;
	double yy = 3.14;
	auto zz = add<int, double>(xx, yy);    //double
	cout << zz << endl;
}

//final和override关键字的使用
class base {
public:
	virtual void test(){
		cout << "base test......" << endl;
	}
};

//多态，继承+重写虚函数+父类的引用指向子类对象
//class child final: public base {   //final修饰类，此类不能被继承
class child : public base {
public:
	//void test() final{         //虚函数被final修饰，不能被重写
	void test() override{        //override检查虚函数重写是否正确
		cout << "child test......" << endl;
	}
};

class grandChild : public child {
public:
	void test() override{
		cout << "grandchild test......" << endl;
	}
};

//模板的优化
//模板的右尖括号
template<class T>
class Container {
public:
	void printContainer(T&t) {
		for (auto it = t.begin(); it != t.end(); it++) {
			cout << "key:" << (*it).first << "  value:" << (*it).second << endl;
		}
	}
};

//函数模板添加默认参数   C++11之前不可以进行添加，C++11可以
template<typename T0 = long, typename T1 = int>
void myTest(T0 t0 = 'A', T1 t1 = 'B'){
	cout << "t0:" << t0 << "  t1:" << t1 << endl;
}

void test6() {
	map<int,string> ma;
	ma.insert(make_pair(1, "zxc"));
	ma.insert(make_pair(2, "asd"));
	ma.insert(make_pair(3, "qwe"));
	Container<map<int, string>> Con;    //在C++11之前模板的>>会将其识别为右移运算符，C++11就不会出现这种情况了
	Con.printContainer(ma);

	myTest('a', 'b');              //自动类型推导   char char
	myTest<int>('a', 'b');         //int char
	myTest<char>('a', 'b');        //char char
	myTest<int, char>('a', 'b');   //显示指定
	myTest<char, int>('a', 'b');   //显示指定
	myTest();                      //没有指定，就使用默认参数

}

int myTest1(int a,string b) {
	cout << "a: " << a << "  b: " << b << endl;
	return 0;
}

typedef int(*func)(int, string);    //给函数指针起别名
using func1 = int(*)(int, string);

template<class T>
class myMap {
public:
	typedef map<int, T> mapType;       //typedef起别名
};

template<class T>
using myMap1 = map<int, T>;             //using起别名

//using的使用  起别名 类似于typedef
void test7() {
	typedef int myInt;
	myInt tt1 = 10;
	cout << "tt1: " << tt1 << endl;
	using myDouble = double;
	myDouble tt2 = 3.14;
	cout << "tt2: " << tt2 << endl;

	func f = myTest1;
	f(10, "zxc");
	func1 f1 = myTest1;
	f1(10, "zxc");

	cout << "-----------------------------------" << endl;
	myMap<int>::mapType mm1;
	myMap<double>::mapType mm2;
	myMap<string>::mapType mm3;

	mm1.insert(make_pair(1, 1));
	mm2.insert(make_pair(1, 3.14));
	mm3.insert(make_pair(1, "hello"));

	Container<myMap<int>::mapType> con1;
	Container<myMap<double>::mapType> con2;
	Container<myMap<string>::mapType> con3;

	con1.printContainer(mm1);
	con2.printContainer(mm2);
	con3.printContainer(mm3);
	cout << "-----------------------------------" << endl;

	myMap1<int> mm4;
	myMap1<double> mm5;
	myMap1<string> mm6;

	mm4.insert(make_pair(1, 1));
	mm5.insert(make_pair(1, 3.14));
	mm6.insert(make_pair(1, "hello"));

	Container<myMap1<int>> con4;
	Container<myMap1<double>> con5;
	Container<myMap1<string>> con6;

	con4.printContainer(mm4);
	con5.printContainer(mm5);
	con6.printContainer(mm6);
	cout << "-----------------------------------" << endl;

}

//int main() {
//	//test4();
//	//test5();
//	//test6();
//	test7();
//
//	system("pause");
//	return 0;
//
//}