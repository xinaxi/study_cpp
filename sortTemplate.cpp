//шаблоны

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

template <typename T>
void swap(T *a, T *b) {
	T t = *a;
	*a = *b;
	*b = t;
}

template <typename T>
void sort(T *a, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[i])
				swap(&a[i], &a[j]);
}

template <typename T>
int test(T *a, int n) {
	for (int i = 0; i < n - 1; i++)
		if (a[i] > a[i + 1]) { return 0; }
	return 1;
}

class myClass {
	int property1;
	float property2;
public:
	myClass(int a, double b) {
		property1 = a;
		property2 = b;
	}
	int operator<(const myClass &b) const {
		if (property1 < b.property1) return 1;
		if (property1 > b.property1) return 0;
		if (property2 < b.property2) return 1;
		return 0;
	}
	int operator>(const myClass &b) const {
		if (*this < b) return 0;
		if ((property1 == b.property1) && (property2 == b.property2)) return 0;
		return 1;
	}
};

void main() {
	int n = 40;
	int *a = (int*)malloc(n * sizeof(int));
	srand(time(NULL));
	int flag = 0;
	int k = 0;
	while (k++ < 200) {
		for (int i = 0; i < n; i++)
			a[i] = rand() % 1000 - 500;
		sort(a, n);
		if (!test(a, n))
			flag = 1;
	}
	if (flag)
		printf(":(\n");
	else printf(":)\n");
	free(a);

	myClass *A = (myClass*)malloc(n * sizeof(myClass));
	flag = 0;
	k = 0;
	while (k++ < 200) {
		for (int i = 0; i < n; i++) {
			int a = rand() % 1000 - 500;
			int b = rand() % 1000 - 500;
			if (!b) b++;
			float c = (rand() % 1000 - 500) / b;
			A[i] = myClass(a, c);
		}
		sort(A, n);
		if (!test(A, n))
			flag = 1;
	}
	if (flag)
		printf("myClass\n");
	else
		printf("Ok\n");
	free(A);
}
