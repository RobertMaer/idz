#include "stack.h"
#include <iostream>
#include <string>
using namespace std;

void StackList::fail(int err) const
{
	switch (err)
	{
	case 1:cout << "Нехватка памяти";
		break;
	case 2:cout << "Стек пуст";
		break;
	}
	exit(1);
}

StackList::StackList()
{
	top_ptr = nullptr;
}

StackList::~StackList()
{
	while (!empty()) {
		pop();
	}
}

bool StackList::empty() const {
	return top_ptr == nullptr;
}

void StackList::push(double value)
{
	Node* tmp = nullptr;
	tmp = new (nothrow) Node;
	if (!tmp) fail(1);
	tmp->data = value;
	tmp->next = top_ptr;
	top_ptr = tmp;
	tmp = nullptr;
}

void StackList::push_str(string value_str)
{
	Node* tmp = nullptr;
	tmp = new (nothrow) Node;
	if (!tmp) fail(1);
	tmp->data = value_str;
	tmp->next = top_ptr;
	top_ptr = tmp;
	tmp = nullptr;
}

void StackList::pop()
{
	if (empty()) fail(2);

	Node* tmp = top_ptr;
	top_ptr = top_ptr->next;
	delete tmp;
	tmp = nullptr;
}

string StackList::top() const
{
	if (empty()) fail(2);

	return top_ptr->data;
}

void print(const StackList& st)
{
	cout << "Stack: ";
	Node* iter = st.top_ptr;
	while (iter != nullptr)
	{
		cout << iter->data << " ";
		iter = iter->next;
	}
	cout << endl;
}