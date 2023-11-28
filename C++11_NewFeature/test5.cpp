#include<iostream>
#include<memory>
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

	//ͨ���ƶ����캯���Ϳ������캯�����г�ʼ��
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

unique_ptr<int>function() {
	return unique_ptr<int>(new int(520));
}

//��ռ����ָ��
void test19() {
	//��ռ����ָ���ʼ��
	
	//ͨ�����캯�����г�ʼ��
	unique_ptr<int> ptr13(new int(10));
	
	//ͨ���ƶ����캯�����г�ʼ��
	unique_ptr<int> ptr14 = move(ptr13);
	unique_ptr<int> ptr15 = function();

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


}

int main() {
	//test18();
	test19();

	system("pause");
	return 0;
}