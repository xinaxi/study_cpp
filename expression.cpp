//префиксная запись + исключения

#include <stdio.h>
#define VAR 1
#define NUM 2
#define BO 3

class Exep {};

class DivisionByZero :public Exep {};

class InvalidArguments :public Exep {};

class UnknownVariable :public Exep {};

class UndefinedOperation :public InvalidArguments {
	char name;
public:
	UndefinedOperation(char n) {
		name = n;
	}
	char returnName() { return name; }
};

class BadName :public InvalidArguments {
	char name;
public:
	BadName(char n) {
		name = n;
	}
	char returnName() { return name; }
};

class Expr {
public:
	virtual void print() = 0;
	virtual double calculate(double x) = 0;
	virtual int whatIsIt() = 0;
	virtual char returnName() { return 0; };
	virtual ~Expr() {}
};

class Var :public Expr {
	char name;
public:
	Var(char n) { name = n; }
	void print() { printf("%c", name); }
	double calculate(double x) {
		if (name != 'x')
			throw UnknownVariable();
		return x;
	}
	int whatIsIt() { return VAR; }
	char returnName() { return name; }
};

class Number :public Expr {
	double value;
public:
	Number(double x) { value = x; }
	void print() { printf("%.2f", value); }
	double calculate(double x) { return value; }
	int whatIsIt() { return NUM; }
};

class BinaryOp :public Expr {
	char name;
public:
	Expr *l;
	Expr *r;
	BinaryOp(char n) { name = n; }
	void print() {
		if (name == '+' || name == '-') {
			printf("(");
			l->print();
			printf(" %c ", name);
			r->print();
			printf(")");
		}
		else {
			l->print();
			printf(" %c ", name);
			r->print();
		}
	}
	double calculate(double x) {
		double a, b;
		a = l->calculate(x);
		b = r->calculate(x);
		if (name == '+')
			return a + b;
		else if (name == '-')
			return a - b;
		else if (name == '*')
			return a * b;
		else {
			if (!b)
				throw DivisionByZero();
			return a / b;
		}
	}
	int whatIsIt() { return BO; }
	char returnName() { return name; }
	~BinaryOp() {
		delete l;
		delete r;
	}
};

Expr *arrToExpr2(Expr **arr, int *i) {
	Expr *ex = *(arr + *i);
	int t = ex->whatIsIt();
	if (t == VAR) {
		if (ex->returnName() != 'x')
			throw BadName(ex->returnName());
		Var *a = new Var(ex->returnName());
		(*i)++;
		return a;
	}
	if (t == NUM) {
		Number *a = new Number(ex->calculate(0));
		(*i)++;
		return a;
	}
	char c = ex->returnName();
	if ((c != '+')&(c != '-')&(c != '*')&(c != '/'))
		throw UndefinedOperation(c);
	BinaryOp *a = new BinaryOp(ex->returnName());
	(*i)++;
	a->l = arrToExpr2(arr, i);
	a->r = arrToExpr2(arr, i);
	return a;
}

Expr *arrToExpr(Expr **arr) {
	int i = 0;
	Expr *a;
	a = arrToExpr2(arr, &i);
	return a;
}

void main() {
	Expr **arr;
	Expr *expr;
	int flag = 1;
	double s;

	arr = new Expr*[11];
	arr[0] = new BinaryOp('-');
	arr[1] = new BinaryOp('*');
	arr[2] = new BinaryOp('/');
	arr[3] = new Number(15);
	arr[4] = new Var('x');
	arr[5] = new Number(3);
	arr[6] = new BinaryOp('*');
	arr[7] = new Var('x');
	arr[8] = new BinaryOp('+');
	arr[9] = new Number(1.8);
	arr[10] = new Var('x');

	try { expr = arrToExpr(arr); }
	catch (BadName n) {
		printf("replace '%c' with 'x'\n", n.returnName());
		flag = 0;
	}
	catch (UndefinedOperation n) {
		printf("Undefined operation '%c'\n", n.returnName());
		flag = 0;
	}
	catch (...) {
		printf("Unknown error\n");
		flag = 0;
	}
	if (flag) {
		expr->print();
		printf("\n");

		double x;
		printf("x = ");
		scanf("%lf", &x);
		try { s = expr->calculate(x); }
		catch (DivisionByZero n) {
			printf("division by zero\n");
			flag = 0;
		}
		catch (UnknownVariable n) {
			printf("variable must be 'x'\n");
			flag = 0;
		}
		catch (...) {
			printf("Unknown error\n");
			flag = 0;
		}
		if (flag)
			printf("%.3f\n", s);
	}
}
