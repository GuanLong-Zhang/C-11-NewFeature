#include<iostream>
#include<map>
using namespace std;

//ԭʼ������    R"()"
void test() {
	string s = "D:\hello\world\test.txt";        //�Ὣ\t����ת��
	cout << s << endl;
	string s1 = "D:\\hello\\world\\test.txt";    //ʹ��\\����ת��
	cout << s1 << endl;
	string s2 = R"(D:\hello\world\test.txt)";    //ʹ��ԭʼ����������ת��   ����python�е�r" "
	cout << s2 << endl;
	string s3 = "hello\
				 world\
				 C++\
				 Java";     //��������������Ҫ��\

	cout << s3 << endl;
	string s4 = R"(hello
				   world
				   C++
				   Java)";    //ʹ��ԭʼ�������Ͳ���Ҫ��\

	cout << s4 << endl;

}

void function(int a) {
	cout << "void funcation(int a)������" << endl;
}

void function(char* a) {
	cout << "void funcation(char* a)������" << endl;
}

//ָ���ֵ����    nullptr
void test1() {
	function(10);
	function(NULL);      //��Ȼ���õ���int a  ��ΪNULL��C++�б�ʾ0
	function(nullptr);   //���õ���char* a

	char* p1 = nullptr;   //����ָ�����͵ĳ�ʼ��������ʹ��nullptr����NULL��������������н�׳��
	int* p2 = nullptr;
	double* p3 = nullptr;

}

//constexpr class T {    //���������Զ����������ͣ�����ֱ��ʹ��constexpr�������Σ����ǿ������������
class T{
public:
	int age;
	constexpr T() :age(200){     //constexpr���ι��캯�������������Ϊ�գ����Ҫ���г�ʼ��������ʹ�ó�ʼ���б�

	}
};

constexpr int function1() {       //constexpr���κ����������з���ֵ�����ҷ���ֵ�����ǳ������ʽ
	constexpr int c = 300;
	return c;
}

//constexpr���γ������ʽ    ʹ��constexpr������߳��������Ч�ʣ���Ϊ���ļ��㷢���ڳ������Ľ׶�
void test2() {
	constexpr int a = 100;         //���������������Ϳ���ֱ��ʹ��constexpr��������
	constexpr double b = 3.14;  
	//a = 200;                     //����ֵ�����Խ����޸�
	constexpr T t;                 //constexpr���������
	//t.age = 200;                 //����ֵ�����Խ����޸�
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
	auto i = T::get();     //�Զ������Ƶ������ݴ���������Լ�ȥ����ʹ���������ͣ�����ʾָ������
    cout << "result:" << i << endl;
}

//�Զ������Ƶ� auto
void test3() {
	auto x = 3.14;      //�Զ������Ƶ�  double
	auto y = 10;        //int 
	auto z = 'a';       //char

	int temp = 110;
	auto x1 = &temp;    //int*
	auto* x2 = &temp;   //int
	auto x3 = temp;     //int

	const auto x4 = temp;   //int
	auto x5 = x4;           //��Ȼx4��const int,���ǲ���ָ������ã�����Ϊint
	const auto& x6 = temp;  //int
	auto& x7 = x6;          //const int
	auto* x8 = &x4;         //const int      const int*  ����ָ��  ָ���ֵ�����Ըģ�ָ����Ը�  * const int  ָ�볣��  ָ�򲻿��Ըģ�ָ���ֵ���Ը�
	//*x8 = 100;            //����ֵ�����Ը�
	x8 = &x6;               //ָ����Ը�

	//auto��ʹ�ó���   STL�ı���
	map<int, string> mp;
	mp.insert(make_pair(1, "zxc"));
	mp.insert(make_pair(2, "asd"));
	mp.insert(make_pair(3, "qwe"));
	//for (map<int, string>::iterator it = mp.begin(); it != mp.end(); it++) {
	//	cout << "key:" << (*it).first << " ,value:" << (*it).second << endl;
	//}
	for (auto it = mp.begin(); it != mp.end(); it++) {     //�Ż�
		cout << "key:" << (*it).first << " ,value:" << (*it).second << endl;
	}

	//���ڷ��ͱ��
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