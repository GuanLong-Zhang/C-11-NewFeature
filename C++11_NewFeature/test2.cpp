#include<iostream>
using namespace std;

class T3 {
public:
	int num = 9;
	string txt;
	static const int value = 100;
};

//只有函数声明，实现体为空
int function2(){}
int & function3(){}
int && function4(){}
const int function5(){}
const int & function6(){}
const int && function7(){}
const T3 function8(){}

//自动类型推导 decltype
void test4() {
	int a = 1;
	decltype(a) b = 2;                 //int    
	decltype(a + 3.14) c = 3.1415;     //double
	const int& d = a;
	decltype(d) e = a;                 //const int&
	decltype(T3::value) f = a;         //const int
	T3 t;
	decltype(t.txt) g = "hello world";  //string

	decltype(function2()) h = 0;        //int
	decltype(function3()) i = h;        //int&
	decltype(function4()) j = 0;        //int&&
	decltype(function5()) k = 0;        //int   省略const   就此情况特殊
	decltype(function6()) l = h;        //const int &
	decltype(function7()) m = 0;        //const int &&
	decltype(function8()) n = T3();     //const T3

	
}

int main() {
	test4();
	system("pause");
	return 0;

}