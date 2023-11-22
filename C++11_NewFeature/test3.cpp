#include<iostream>
#include<vector>
#include<map>
using namespace std;

//ί�й��캯���ͼ̳й��캯��
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
	Test(int max, int min):Test(max) {           //ί�й��캯��  һ�����캯����ȥ��������һ�����캯�� �����ظ�����
		this->min = min > 0 && min < max ? min : 1;
	}
	Test(int max, int min, int mid):Test(max, min) {    //ί�й��캯��
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
	base(int i, double j):base(i) {     //ί�й��캯��
		this->j = j;
	}
	base(int i, double j, string k):base(i,j) {     //ί�й��캯��
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
	using base::base;          //ʹ�ø�������й��캯��   �̳й��캯��
	using base::func;          //ʹ�ñ��������صĸ��ຯ������Ҫ��using������Ӵ˾䣬֮����ûᱨ��
	void func() {
		cout << "child func() ......" << endl;
	}
};

void test8() {
	//child ch(3);
	//child ch(3, 3.14);
	child ch(3, 3.14, "hello C++");     //���캯����ʼ��   �̳��Ը���Ĺ��캯��
	cout << "i = " << ch.getInt() << "  j = " << ch.getDouble() << "  k = " << ch.getString() << endl;
	ch.func();      //��������func
	ch.func(10);    //���ø���func
}

//��ʼ���б�
void test9() {
	int arr1[] = { 1,2,3 };
	int arr2[]{ 1,2,3 };          //�Ⱥſ���ʡ��
	base b(3,3.14,"world");       //ʹ�ù��캯�����г�ʼ��
	cout << "i = " << b.getInt() << "  j = " << b.getDouble() << "  k = " << b.getString() << endl;
	base b1{6,6.14,"hello"};      //ʹ�ó�ʼ���б���г�ʼ��   �Ǿۺ���ʹ�ó�ʼ���б���Ҫ���Զ��幹�캯�� {}��ͬ��()
	cout << "i = " << b1.getInt() << "  j = " << b1.getDouble() << "  k = " << b1.getString() << endl;
}


//initializer_list   ��һ������
void function(initializer_list<int> ls) {
	for (auto it = ls.begin(); it != ls.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test10() {
	function({ 1,2,3,4,5,6 });    //ʹ�ó�ʼ���б������г�ʼ��

}

//���ڷ�Χ��forѭ��   (����java�е���ǿfor)
void test11() {
	vector<int> ve {1,2,3,4,5,6};     //��ʼ���б���г�ʼ��
	//ԭʼforѭ������
	for (auto it = ve.begin(); it != ve.end(); it++) {     //�Զ������Ƶ�
		cout << *it << " ";
	}
	cout << endl;
	cout << "---------------------------" << endl;

	//���ڷ�Χ��forѭ��
	for (auto it : ve) {         //�Զ������Ƶ�
		cout << it << " ";
	}
	cout << endl;
	cout << "---------------------------" << endl;

	//���ڷ�Χ��forѭ��    (�Ľ�)  ͨ������&�����Ըı��������������
	for (auto &it : ve) {         //�Զ������Ƶ�
		cout << ++it << " ";
	}
	cout << endl;
	cout << "---------------------------" << endl;

	map<int, string> ma;
	ma.insert(make_pair(1, "zxc"));
	ma.insert(make_pair(2, "asd"));

	for (auto& it : ma) {         //�Զ������Ƶ�   �Ƶ������Ƕ�������
		cout << it.first << " " << it.second << endl;
	}
	cout << "---------------------------" << endl;

	for (auto it = ma.begin(); it != ma.end(); it++)  {         //�Զ������Ƶ�   �Ƶ������ǵ�����
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