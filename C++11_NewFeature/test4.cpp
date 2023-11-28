#include<iostream>
#include<functional>
#include<list>
using namespace std;

//�ɵ��ö����װ�� ����
//�ɵ��ö���
//����ָ��
void print(int num, string name) {     //��ͨ����
	cout << "��ͨ����  num: " << num << "   name: " << name << endl;
}
using func = void(*)(int, string);   //����ָ��

//�º���   ����С����
class Test {
public:
	int mid = 10;
public:
	void operator()(string name) {
		cout << "�º���    name: " << name << endl;
	}

	//����ת��Ϊ����ָ��������
	operator func() {
		return world;
	}

	void hello(int num, string name) {              //û�б�static���εĳ�Ա���������ڶ��󣬲�������
		cout << "hello���� num: " << num << "   name: " << name << endl;
	}

	static void world(int num, string name) {       //static���γ�Ա�������ú���������
		cout << "world���� num: " << num << "   name: " << name << endl;
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
	func f = print;                  //����ָ��ָ����ͨ����
	f(1, "zxc");

	Test t;
	t("zxc");                        //���÷º���

	Test t1;
	t1(1, "zxc");                    //�����ת��Ϊ����ָ��

	func f1 = Test::world;           //���Ա����ָ��   ����ָ��ָ��̬��Ա����
	f1(1, "zxc");
	using func1 = void(Test::*)(int, string);   //���¶��庯��ָ�룬������ʱ������������������Կ��Է��ʷǾ�̬��Ա������
	func1 f2 = &Test::hello;

	using func2 = int Test::*;       //���Ա����ָ��
	func2 f3 = &Test::mid;

	Test t2;                         //������ָ������ã�Ȼ�����
	(t2.*f2)(1, "zxc");
	t2.*f3 = 100;
	cout << "mid = " << t2.mid << endl;
	cout << "---------------------------------" << endl;

	//�ɵ��ö����װ��
	//��װ��ͨ����
	function<void(int, string)> f4 = print;
	f4(2, "asd");
	//��װ��ľ�̬��Ա����
	function<void(int, string)> f5 = Test::world;
	f5(2, "asd");
	//��װ�º���
	Test t3;
	function<void(string)> f6 = t3;
	f6("asd");
	//��װת��Ϊ����ָ��������
	Test t4;
	function<void(int, string)> f7 = t4;
	f7(2, "asd");
	cout << "---------------------------------" << endl;

	A a1(print);                  //������ͨ����
	a1.notify(3, "qwe");

	A a2(Test::world);            //������ľ�̬��Ա����
	a2.notify(3, "qwe");

	//Ҳ���Դ���º��������Ƿº���������notify�������Ͳ�ƥ�䣬���Ծ�û�н��в���

	A a4(t4);                     //����ת��Ϊ����ָ��������
	a4.notify(3, "qwe");
	cout << "---------------------------------" << endl;

	//�ɵ��ö������   
	//�ɰ󶨷����Ա����/������Ҳ�ɰ����Ա����/����
	//�����Ա����/����
	bind(output, 1, 2)();                                        //1 2
	bind(output, placeholders::_1, 2)(1);                        //1 2     placeholders::_1 ռλ��
	bind(output, 1, placeholders::_1)(2);                        //1 2

	bind(output, 1, placeholders::_2)(10, 2);                    //1 2
	bind(output, placeholders::_1, placeholders::_2)(1, 2);      //1 2
	cout << "---------------------------------" << endl;

	for (int i = 0; i < 10; i++) {
		//auto f = bind(output_add, i + 100, i + 200);  //û��ʹ��ռλ����������ָ��û������
		//testFunc(i, i, f);
		auto f8 = bind(output_add, placeholders::_1 ,placeholders::_2);  //���ռλ���������Ĳ����ſ�����Ч
		testFunc(i, i, f8);
	}
	cout << "---------------------------------" << endl;

	//���Ա����/����
	B b;
	auto f9 = bind(&B::output_B, &b, 520, placeholders::_1);  //f9Ϊһ���º���
	f9(1314);
	//��װ + ��
	function<void(int, int)> f9_1 =  bind(&B::output_B, &b, placeholders::_1, placeholders::_2);
	f9_1(520, 1314);


	auto f10 = bind(&B::num, &b);                             //f10Ϊһ���º���
	cout << "num = " << f10() << endl;
	f10() = 200;
	cout << "num = " << f10() << endl;
	//��װ + ��
	function<int& (void)> f10_1 = bind(&B::num, &b);
	cout << "num = " << f10_1() << endl;
	f10_1() = 300;
	cout << "num = " << f10_1() << endl;

}

//lambda���ʽ
void assign(int x, int y) {
	int a = 1;
	int b = 2;
	[=, &x]() mutable{        //��x�ǰ������ò���ģ�����Ķ���ֵ����   Ҫ�޸�ֻ�����ݣ���Ҫ��mutable
		int c = a;
		int d = x;
		b++;
		cout << "b = " << b << endl;   //��Ȼֵ�����˱仯������ֵ�������βθı䲻Ӱ��ʵ��,�ⲿb���ᷢ���ı�
	}();        //������Ҫ��()
	cout << "b = " << b << endl;
}

class C {
public:
	void output(int x, int y) {
		auto x1 = [=]() {return number + x + y; }();     //��ֵ����    ֻ��
		auto x2 = [&]() {return number + x + y; }();     //�����ò���
		auto x3 = [this]() {return number; }();          //�����Ա����/����
		auto x4 = [this, x, y]() {return number + x + y; }();  //�����Ա����/���� �Լ� x y 
		cout << "x1 = " << x1 << " x2 = " << x2 << " x3 = " << x3 << " x4 = " << x4 << endl;

	}
private:
	int number = 100;
};

void toPtr(int x, int y) {
	using ptr = void (*)(int);              //����ָ��
	ptr p1 = [](int z0) {                   //�ղ��񣬿���ת��Ϊһ������ָ��
		cout << "z0 = " << z0 << endl;
	};
	p1(10);

	function<void(int)> f11 = [=](int z1) {        //lambda���ʽ������һ���º���,ʹ�ð�װ�����н���
		cout << "z1 = " << z1 << endl;
	};
	f11(20);

	function<void(int)> f12 = bind([=](int z2) {       //��ʹ�ð������а�,Ȼ��ʹ�ð�װ�����н���
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

//��ֵ����ֵ���� ��ֵ����ֵ����
class D {
private:
	int* myNum;
public:
	D() : myNum(new int(100)) {
		cout << "�޲ι��캯��������" << endl;
	}

	D(const D& d1) : myNum(new int(*d1.myNum)) {    //���
		cout << "�������캯��������" << endl;
	}

	//�ƶ����캯��  ����ǳ����   ���ö��ڴ�ռ�
	D(D&& d1) : myNum(d1.myNum) {
		d1.myNum = nullptr;
		cout << "�ƶ����캯��������" << endl;
	}

	~D() {
		cout << "��������������" << endl;
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
	//��ֵnum
	int num = 9;
	//��ֵ����    �൱�ڸ�num�����  ��ֵ����a
	int& a = num;
	//��ֵ �� ��ֵ����
	int&& b = 10;      //��ֵ10����ֵ����b  ��Ҫ��&&
	//������ֵ����
	const int&& d = 100;
	//������ֵ����
	const int& c = num;   //��ֵ��ʼ��
	const int& c1 = a;    //��ֵ���ó�ʼ��
	const int& c2 = b;    //��ֵ���ó�ʼ��
	const int& c4 = d;    //������ֵ���ó�ʼ��

	D obj;
	D obj1 = obj;    //���������ʱ�򡣽�obj����obj1    ���ÿ������캯��
	D obj2 = move(obj);   //moveǿ�ƽ���ֵת��Ϊ��ֵ�������ƶ����캯��
	
	//D obj3 = getObj();   //getObj()Ϊ��ʱ���������ص�ֵΪ��ֵ������ȴû�е��õ��ƶ����캯��
	//D &&obj4 = getObj1();
	//D&& obj5 = getObj2();
}

//δ������������͵��Ƶ�   
//������&&,a������ֵ���ã���Ҫ���ݴ����ʵ�ν����Ƶ�
//������ֵ�����Ƶ���������ֵ���ã��������ֵ����ô�Ƶ���Ϊ��ֵ����
template<typename T>
void funcT(T&& a) {
	cout << "ģ�庯��������" << endl;
}

void test15() {
	funcT(10);     //������ֵ��aΪ��ֵ����
	int xT = 10;   //xTΪ��ֵ
	funcT(xT);     //������ֵ��aΪ��ֵ����   ����ʵ���Ƿ���ֵ��a������ֵ����

	//����ֵ��������ֵ����ֵ���ã���ֵ���ã�������ֵ���ã�������ֵ����  

	auto&& aT = xT;    //������ֵ��aTΪ��ֵ����
	auto&& aT1 = 250;  //������ֵ��aT1Ϊ��ֵ����
	int&& v1 = 100;    //v1Ϊ��ֵ����
	auto&& v2 = v1;    //v2Ϊ��ֵ���ã���Ϊ����Ĳ�������ֵ����
	int& v3 = xT;      //v3Ϊ��ֵ����
	auto&& v4 = v3;    //v4Ϊ��ֵ���ã���Ϊ����Ĳ�������ֵ����
	const int& v5 = xT;    //v5Ϊ������ֵ����
	auto&& v6 = v5;        //v6Ϊ������ֵ���ã���Ϊ����Ĳ����ǳ�����ֵ���� 
	const int&& v7 = 300;  //v7Ϊ������ֵ����
	auto&& v8 = v7;        //v8Ϊ������ֵ���ã���Ϊ����Ĳ����ǳ�����ֵ����   

}

//��ֵ���õĴ���
//��ֵ�����ڴ��ݵ�ʱ�򣬻����ת��Ϊ��ֵ����
void printValue(int&& a) {
	cout << "��ֵ���ú���������a = " << a << endl;
}

void printValue(int& a) {
	cout << "��ֵ���ú���������a = " <<a << endl;
}

void forward(int&& a) {   //int&& a����a��һ����ֵ�������ڴ��ݵ�ʱ��Ὣ��ת��Ϊ��ֵ
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
	cout << "��ֵ���ú���������t = " << t << endl;
}

template<typename T>
void printKey(T&& t) {
	cout << "��ֵ���ú���������t = " << t << endl;
}

template<typename T>
void testForward(T&& t) {     //�Զ������Ƶ�������ֵ����Ϊ��ֵ����
	printKey(t);              //��ֵ�����ڴ��ݵ�ʱ�򣬻�����ֵ����
	printKey(move(t));        //��ֵת��ֵ
	printKey(forward<T>(t));   //��TΪ��ֵ���ã�t��Ϊ��ֵ����TΪ����ֵ���ã���ôt��Ϊ��ֵ
	cout << endl;

}

//ת�ƺ�����ת��  move forward
void test17() {
	int Aa = 10;             //AaΪһ����ֵ
	int&& Bb = move(Aa);     //ֱ��ʹ����ֵ����ֵ���ó�ʼ���ᱨ������ʹ��move����ֵת��Ϊ��ֵ��������ֵ���õĳ�ʼ��

	list<string> l1 = { "hello","world","C++","Java" };
	list<string>l2 = move(l1);   //ʹ��move������Դת�ƣ����Ч�ʡ�  l1֮�󲻻ᱻʹ�ã�������Ҫ������l2,��ô�Ϳ���ʹ��move������Դת�ƣ����Ч��

	testForward(520);    //�� �� ��
	testForward(Aa);     //�� �� ��
	testForward(forward<int>(Aa));   //�� �� ��
	testForward(forward<int&>(Aa));  //�� �� ��
	testForward(forward<int&&>(Aa)); //�� �� ��
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