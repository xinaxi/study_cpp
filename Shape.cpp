//абстрактный класс + исключения

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI (3.141592653589793)

class Exep {};

class Tex :public Exep {
	char name;
public:
	Tex(char n) {
		name = n;
	}
	const char returnName() { return name; }
};

class Shape{
public:
	virtual double square() = 0;
	virtual void print() = 0;
};

class Triangle : public Shape{
	double a;
	double b;
	double c;
public:
	Triangle(double A, double B, double C){
		if ((A + B) < C){
			throw Tex('C');
		}
		if ((A + C) < B){
			throw Tex('B');
		}
		if ((C + B) < A){
			throw Tex('A');
		}
		a = A;
		b = B;
		c = C;
	}
	double square() {
		double p = (a + b + c) / 2;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}
	void print() {
		printf("Triangle\n  a = %.3f\n  b = %.3f\n  c = %.3f\n  square = %.3f\n", a, b, c, square());
	}
};

class Rectangle : public Shape{
	double a;
	double b;
public:
	Rectangle(double A, double B) : a(A), b(B){}
	double square() { return a*b; }
	void print() {
		printf("Rectangle\n  a = %.3f\n  b = %.3f\n  square = %.3f\n", a, b, square());
	}
};

class Square : public Rectangle{
	double a;
public:
	Square(double A) : Rectangle(A, A){
		a = A;
	}
	double square() { return a*a; }
	void print() {
		printf("Square\n  a = %.3f\n  square = %.3f\n", a, square());
	}
};

class Circle : public Shape{
	double r;
public:
	Circle(double R) : r(R){}
	double square() { return PI*r*r; }
	void print() {
		printf("Circle\n  r = %.3f\n  square = %.3f\n", r, square());
	}
};

void main() {
	double a, b, c;
	a = 12.444;
	b = 43;
	c = (double)9 / 7;
	printf("a  %f\nb  %f\nc  %f\n", a, b, c);
	try { Triangle T2(a, b, c); }
	catch (Tex n) {
		printf("Side %c less then the sum of two other sides\n", n.returnName());
	}
	Triangle T(a, 13, c);
	T.print();
	Rectangle R(b, c);
	R.print();
	Square S(a);
	S.print();
	Circle C(c);
	C.print();
}
