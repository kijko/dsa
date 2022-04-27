#include <stdio.h>

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}

	if (a == 0) {
		return b;
	}

	int ap = a % b;
	
	return gcd(b, ap);
}

int main(void) {
	int a,b;
	scanf("%d", &a);
	scanf("%d", &b);

	printf("%d", gcd(a, b));
	return 0;
}


