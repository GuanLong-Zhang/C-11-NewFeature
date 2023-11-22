#include<iostream>
#include<vector>
#include<map>
using namespace std;

//委托构造函数和继承构造函数
class Test {
private:
	int max;
	int min;
	int mid;
public:
	Test(){}
	Test(int max) {
		this->max = max > 0 ? max : 100;
	}
	Test(int max, int min):Test(max) {           //委托构造函数  一个构造函数中去调用另外一个构造函数 减少重复代码
		this->min = min > 0 && min < max ? min : 1;
	}
	Test(int max, int min, int mid):Test(max, min) {    //委托构造函数
		this->mid = mid < max && mid > min ? mid : 50;
	}

};

class base {
private:
	int i;
	double j;
	string k;
public:
	base(int i) {
		this->i = i;
	}
	base(int i, double j):base(i) {     //委托构造函数
		this->j = j;
	}
	base(int i, double j, string k):base(i,j) {     //委托构造函数
		this->k = k;
	}
	int getInt() {
		return i;
	}
	
	double getDouble() {
		return j;
	}

	string getString() {
		return k;
	}

	void func(int i) {
		cout << "base func(int i) ......" << endl;
	}

};

class child : public base {
private:
	int i;
	double j;
	string k;
public:
	using base::base;          //使用父类的所有构造函数   继承构造函数
	using base::func;          //使用被子类隐藏的父类函数，需要用using，不添加此句，之后调用会报错
	void func() {
		cout << "child func() ......" << endl;
	}
};

void test8() {
	//child ch(3);
	//child ch(3, 3.14);
	child ch(3, 3.14, "hello C++");     //构造函数初始化   继承自父类的构造函数
	cout << "i = " << ch.getInt() << "  j = " << ch.getDouble() << "  k = " << ch.getString() << endl;
	ch.func();      //调用子类func
	ch.func(10);    //调用父类func
}

//初始化列表
void test9() {
	int arr1[] = { 1,2,3 };
	int arr2[]{ 1,2,3 };          //等号可以省略
	base b(3,3.14,"world");       //使用构造函数进行初始化
	cout << "i = " << b.getInt() << "  j = " << b.getDouble() << "  k = " << b.getString() << endl;
	base b1{6,6.14,"hello"};      //使用初始化列表进行初始化   非聚合体使用初始化列表需要有自定义构造函数 {}等同于()
	cout << "i = " << b1.getInt() << "  j = " << b1.getDouble() << "  k = " << b1.getString() << endl;
}


//initializer_list   是一个容器
void function(initializer_list<int> ls) {
	for (auto it = ls.begin(); it != ls.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test10() {
	function({ 1,2,3,4,5,6 });    //使用初始化列表对其进行初始化

}

//基于范围的for循环   (类似java中的增强for)
void test11() {
	vector<int> ve {1,2,3,4,5,6};     //初始化列表进行初始化
	//原始for循环遍历
	for (auto it = ve.begin(); it != ve.end(); it++) {     //自动类型推导
		cout << *it << " ";
	}
	cout << endl;
	cout << "---------------------------" << endl;

	//基于范围的for循环
	for (auto it : ve) {         //自动类型推导
		cout << it << " ";
	}
	cout << endl;
	cout << "---------------------------" << endl;

	//基于范围的for循环    (改进)  通过增加&，可以改变容器里面的内容
	for (auto &it : ve) {         //自动类型推导
		cout << ++it << " ";
	}
	cout << endl;
	cout << "---------------------------" << endl;

	map<int, string> ma;
	ma.insert(make_pair(1, "zxc"));
	ma.insert(make_pair(2, "asd"));

	for (auto& it : ma) {         //自动类型推导   推导出的是对组引用
		cout << it.first << " " << it.second << endl;
	}
	cout << "---------------------------" << endl;

	for (auto it = ma.begin(); it != ma.end(); it++)  {         //自动类型推导   推导出的是迭代器
		cout << (*it).first << " " << (*it).second << endl;
	}
	cout << "---------------------------" << endl;

}

//int main() {
//	//test8();
//	//test9();
//	//test10();
//	test11();
//
//	system("pause");
//	return 0;
//}