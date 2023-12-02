#include<iostream>
#include<memory>
#include<functional>
using namespace std;

class Test {
private:
	int num;
public:
	Test() {
		cout << "�޲ι��캯��" << endl;
	}

	Test(int i) :num(i) {
		cout << "���͹��캯��" << endl;
	}

	Test(string s){
		cout << "�ַ��͹��캯��" << endl;
	}

	~Test() {
		cout << "��������" << endl;
	}

	void setNum(int num) {
		this->num = num;
	}

	void printNum() {
		cout << "num = " << num << endl;
	}

};

//ɾ�������ڴ�ģ�庯��
template<typename T>
shared_ptr<T> make_share_array(size_t size) {
	return shared_ptr<T>(new T[size], default_delete<T[]>());
}

//����ָ��
//��������ָ��
void test18() {
	//��������ָ��ĳ�ʼ��
	
	//ͨ�����캯�����г�ʼ��
	shared_ptr<int> ptr1(new int(3));
	cout << "ptr1.use_count = " << ptr1.use_count() << endl;
	cout << "-------------------------------------------" << endl;

	//ͨ���ƶ����캯���Ϳ������캯�����г�ʼ��    ʹ��use_count()���Բ鿴ʹ�û���
	shared_ptr<int> ptr2 = move(ptr1);                           //�������ƶ�
	cout << "ptr1.use_count = " << ptr1.use_count() << endl;     //0
	cout << "ptr2.use_count = " << ptr2.use_count() << endl;     //1
	shared_ptr<int> ptr3 = ptr2;                                 //�����˿���
	cout << "ptr2.use_count = " << ptr2.use_count() << endl;     //2
	cout << "ptr3.use_count = " << ptr3.use_count() << endl;     //2
	cout << "-------------------------------------------" << endl;

	//ͨ��make_shared���г�ʼ��
	shared_ptr<int> ptr4 = make_shared<int>(4);
	shared_ptr<Test> ptr5 = make_shared<Test>();              //�޲�
	shared_ptr<Test> ptr6 = make_shared<Test>(5);             //����
	shared_ptr<Test> ptr7 = make_shared<Test>("hello");       //�ַ���
	cout << "ptr4.use_count = " << ptr4.use_count() << endl;     //1
	cout << "ptr5.use_count = " << ptr5.use_count() << endl;     //1
	cout << "ptr6.use_count = " << ptr6.use_count() << endl;     //1
	cout << "ptr7.use_count = " << ptr7.use_count() << endl;     //1
	cout << "-------------------------------------------" << endl;

	//ͨ��reset���г�ʼ��
	ptr4.reset();                                                //����ָ��
	cout << "ptr4.use_count = " << ptr4.use_count() << endl;     //0
	ptr4.reset(new int(6));                                      //����ָ���µ��ڴ�ռ�
	cout << "ptr4.use_count = " << ptr4.use_count() << endl;     //1
	cout << "-------------------------------------------" << endl;

	//��������ָ���ʹ��

	//ͨ��get���ԭʼ��ַ��Ȼ��ͨ��ԭʼ��ַ���в���
	Test *t = ptr6.get();
	t->setNum(999);
	t->printNum();

	//ͨ����������ָ�����ֱ�ӽ��в���
	ptr6->setNum(888);
	ptr6->printNum();
	cout << "-------------------------------------------" << endl;

	//ɾ����
	shared_ptr<Test>ptr8(new Test(666), [](Test* t) {cout << "ɾ����1������" << endl;  delete t; }); //ɾ������lambda���ʽ������
	cout << "ptr8.use_count = " << ptr8.use_count() << endl;      //1
	   
	//���������ڴ棬����ָ��ɾ����
	//���ڷ������ڴ棬����ָ��Ĭ��ɾ�����Ϳ���ɾ��
	shared_ptr<Test>ptr9(new Test[5], [](Test* t) {cout << "ɾ����2������" << endl;  delete[]t; });
	cout << "ptr9.use_count = " << ptr9.use_count() << endl;      //1

	//Ĭ��ɾ����
	shared_ptr<Test>ptr10(new Test[5], default_delete<Test[]>());     //����ִ��˳���ȵ��õĺ�����
	cout << "ptr10.use_count = " << ptr10.use_count() << endl;    //1

	//ɾ�������ڴ�ģ�庯��
	shared_ptr<int> ptr11 = make_share_array<int>(10);    //int���� ��СΪ10;
	cout << "ptr11.use_count = " << ptr11.use_count() << endl;     //1
	shared_ptr<char> ptr12 = make_share_array<char>(10);  //char���飬��СΪ10
	cout << "ptr12.use_count = " << ptr12.use_count() << endl;     //1
}

unique_ptr<int>function1() {
	return unique_ptr<int>(new int(520));
}

//��ռ����ָ��
void test19() {
	//��ռ����ָ���ʼ��
	
	//ͨ�����캯�����г�ʼ��
	unique_ptr<int> ptr13(new int(10));
	
	//ͨ���ƶ����캯�����г�ʼ��
	unique_ptr<int> ptr14 = move(ptr13);
	unique_ptr<int> ptr15 = function1();

	//ͨ��reset���г�ʼ��
	ptr14.reset();                //����ָ��
	ptr14.reset(new int(100));    //��ָ��ָ���µ��ڴ�ռ�

	//��ռ����ָ���ʹ��
	
	//ͨ��get���ԭʼ��ַ��Ȼ��ͨ��ԭʼ��ַ���в���
	unique_ptr<Test> ptr16(new Test(666));
	Test* t = ptr16.get();
	t->setNum(1000);
	t->printNum();

	//ͨ����ռ����ָ�����ֱ�ӽ��в���
	ptr16->setNum(2000);
	ptr16->printNum();

	//ɾ����

	//�͹�������ָ��ɾ��������������Ҫָ��ɾ����������
	//û�в�������lambda���ʽ���Ա����ɺ���ָ��
	using ptrType = void(*)(Test*);      //using������ָ�������   
	unique_ptr<Test, ptrType> ptr17(new Test("hello"), [](Test* t) {cout << "ɾ����3������" << endl; delete t; });
	
	//�в�������lambda���ʽ��һ���º���,��Ҫ�ð�װ��������а�װ
	unique_ptr<Test, function<void(Test*)>> ptr18(new Test(100), [=](Test* t) {cout << "ɾ����4������" << endl; delete t; });

	//��ռ����ָ����Թ��������ڴ棬�ܹ��Զ��ͷţ�����Ҫ��������ָ����������ָ��ɾ����
	unique_ptr<Test[]>ptr19(new Test[5]);

	//��C++11�У���������ָ�벻�ܹ��������ڴ棬������C++11֮��Ϳ�����
	shared_ptr<Test[]>ptr20(new Test[5]);
}

//����������ָ��   ������������ָ�빤����
void test20() {
	 //����������ָ���ʼ��
	shared_ptr<int> sp(new int);
	weak_ptr<int> wp;

	weak_ptr<int> wp1(sp);    //ͨ��shared_ptr������г�ʼ��    ʵ����
	weak_ptr<int> wp2(wp);    //ͨ��weak_ptr������г�ʼ��      δʵ����

	weak_ptr<int> wp3;
	wp3 = sp;

	weak_ptr<int> wp4;
	wp4 = wp;

	//���÷���
	//use_count()   �鿴��Դ���û�����
	cout << "sp = " << sp.use_count() << endl;       //1
	cout << "wp = " << wp.use_count() << endl;       //0    δʵ�������������û���Ϊ0
	cout << "wp1 = " << wp1.use_count() << endl;     //1
	cout << "wp2 = " << wp2.use_count() << endl;     //0    
	cout << "wp3 = " << wp3.use_count() << endl;     //1
	cout << "wp4 = " << wp4.use_count() << endl;     //0

	//expired()   �鿴��Դ�Ƿ��ͷ�(�����û����Ƿ�Ϊ0)    �ͷŷ���true
	cout << "wp " << (wp.expired() ? "is" : "is not") << " expired" << endl;
	cout << "wp1 " << (wp1.expired() ? "is" : "is not") << " expired" << endl;
	wp1.reset();      //����ָ��
	cout << "wp1 " << (wp1.expired() ? "is" : "is not") << " expired" << endl;

	//lock()  �õ��������Դ��shared_ptr����    reset() ����weak_ptr
	shared_ptr<int> sp1, sp2;
	weak_ptr<int> wpp;

	sp1 = make_shared<int>(520);
	wpp = sp1;
	sp2 = wpp.lock();
	cout << "wpp = " << wpp.use_count() << endl;
	
	sp1.reset(); 
	cout << "wpp = " << wpp.use_count() << endl;

	sp1 = wpp.lock();
	cout << "wpp = " << wpp.use_count() << endl;

}

class TE : public enable_shared_from_this<TE>{
public:
	shared_ptr<TE> getshared_ptr() {
		return shared_ptr<TE>(this);     //���ûᱨ��
	}

	shared_ptr<TE> getshared_ptr_1() {
		return shared_from_this();      //this����Ľ������
	}

	~TE() {
		cout << "��������������" << endl;
	}
};

class TA;
class TB;

class TA {
public:
	//shared_ptr<TB> bptr;
	weak_ptr<TB> bptr;        //�������ָ��ѭ���������⣬����ʹ��weak_ptr������shared_ptr
	~TA(){
		cout << "TA��������������" << endl;
	}
};

class TB {
public:
	shared_ptr<TA>aptr;
	~TB() {
		cout << "TB��������������" << endl;
	}
};


//shared_ptr��ʹ��ע������   3��
void test21() {
	//TE *te = new TE;
	//shared_ptr<TE>ptr1(te);      //����ʹ��ͬһ��ԭʼ��ַ��ʼ�����shared_ptr   
	//cout << "ptr1 = " << ptr1.use_count() << endl;
	////shared_ptr<TE>ptr2(te);    //����ͬһ���ڴ汻��������
	//shared_ptr<TE> ptr2 = ptr1;  //�������캯�����г�ʼ��
	//cout << "ptr2 = " << ptr2.use_count() << endl;

	//shared_ptr<TE>ptr3(new TE);
	//cout << "ptr3 = " << ptr3.use_count() << endl;
	////shared_ptr<TE>ptr4 = ptr3->getshared_ptr();  //����getshared_ptr()����thisָ��,��ô��ָ����ͬһ��ԭʼ��ַ��ͬһ���ڴ汻��������
	//shared_ptr<TE>ptr4 = ptr3->getshared_ptr_1();  //�������  �̳�enable_shared_from_this<>,Ȼ��return shared_from_this()
	//cout << "ptr4 = " << ptr4.use_count() << endl;

	shared_ptr<TA> ptr5(new TA);
	shared_ptr<TB> ptr6(new TB);
	cout << "ptr5 = " << ptr5.use_count() << endl;   //1
	cout << "ptr6 = " << ptr6.use_count() << endl;   //1

	ptr5->bptr = ptr6;    //ѭ�����ã�shared_ptr�޷��ͷţ��޷�������������������ڴ�й©
	ptr6->aptr = ptr5;
	cout << "ptr5 = " << ptr5.use_count() << endl;   //2
	cout << "ptr6 = " << ptr6.use_count() << endl;   //1
	//���ѭ�����õķ�������ʹ��weak_ptr�����ѭ������
}

int main() {
	//test18();
	//test19();
	//test20();
	test21();

	system("pause");
	return 0;
}