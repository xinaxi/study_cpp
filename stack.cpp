//стек + шаблоны + исключения

#include <stdio.h>
#include <stdlib.h>

class Exep {};
class EmptyStack : public Exep {};

template <typename T>
struct StackElem {
	T value;
	StackElem<T> *next;
	StackElem(T v, StackElem<T>* n) : value(v), next(n) {}
};

template <typename T>
class Stack {
	StackElem<T> *head;
public:
	Stack() {
		head = NULL;
	}
	void push(T val) {
		StackElem<T> *x = new StackElem<T>(val, head);
		head = x;
	}
	void pop() {
		if (!head) { throw EmptyStack(); }
		StackElem<T> *x;
		x = head->next;
		delete(head);
		head = x;
	}
	T top() {
		if (!head) { throw EmptyStack(); }
		return head->value;
	}
};

class myClass {
	int property1;
	float property2;
public:
	myClass(int a, double b) {
		property1 = a;
		property2 = b;
	}
	void print() {
		printf("  pr1 = %3d\n  pr2 = %7.3f\n", property1, property2);
	}
};

void main() {
	try {
		myClass A(3, 7.1);
		myClass B(11, 7.9);
		printf("A\n");
		A.print();
		printf("B\n");
		B.print();
		Stack<myClass> s;
		s.push(A);
		s.top();
		s.push(B);
		printf("top\n");
		s.top().print();
		s.pop();
		printf("top\n");
		s.top().print();
		s.pop();
		printf("top\n");
		s.top().print();
		s.pop();
	}
	catch (EmptyStack n) {
		printf("Stack is empty!\n");
	}
	catch (...) {
		printf("Unknown error\n");
	}
}
