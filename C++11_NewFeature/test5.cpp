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
//����ָ��
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
}

int main() {
	test18();
	system("pause");
	return 0;
}