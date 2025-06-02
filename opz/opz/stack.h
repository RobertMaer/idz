#include <string>
using namespace std;
struct Node
{
	string data;
	Node* next;
};

class StackList
{
private:
	Node* top_ptr; // ��������� �� ������� �����
	void fail(int) const; // ���������� ������

public:
	StackList(); // �����������
	~StackList(); //����������
	bool empty() const; // �������� �� �������
	void push(double); //�������� � ����
	void push_str(string); //�������� � ����
	void pop(); // ������� ������� �����
	string top() const; // ���������� �������
	friend void print(const StackList&);
};
