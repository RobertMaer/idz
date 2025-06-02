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
	Node* top_ptr; // указатель на вершину стека
	void fail(int) const; // обработчик ошибок

public:
	StackList(); // конструктор
	~StackList(); //деструктор
	bool empty() const; // проверка на пустоту
	void push(double); //положить в стек
	void push_str(string); //положить в стек
	void pop(); // удалить вершину стека
	string top() const; // посмотреть вершину
	friend void print(const StackList&);
};
