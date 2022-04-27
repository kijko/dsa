#include <stdio.h>

long long fiboLastDigit(int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	}

	unsigned long long memory[n+1];
	memory[0]=0;
	memory[1]=1;

	int i;
	for (i = 2; i <= n; i++) {
		memory[i]=(memory[i-1] + memory[i-2]) % 10;
	}


	return memory[n];
}

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%lld", fiboLastDigit(n));

	return 0;
}

