#include "my.h"

#define N 8

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))

int main(void) {
	int a = N;
	int b = 33;
	int c = foo(min(a, b));

	float d = 28.764f;

	return 0;
}
