#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

long calc(long n) {
	int T[n], res[3], min;
	long s1, s3, s4;

	for (long num = 1; num <= n; num++) {
		s1 = num - 1;
		res[0] = s1 == 0 ? 1 : T[s1 - 1] + 1;

		s3 = num - 3;
		res[1] = s3 == 0 ? 1 : (s3 < 0 ? -1 : T[s3 - 1] + 1);

		s4 = num - 4;
		res[2] = s4 == 0 ? 1 : (s4 < 0 ? -1 : T[s4 - 1] + 1);

		min = INT_MAX;
		for (int i = 0; i < 3; i++) if (res[i] != -1 && res[i] < min) min = res[i];
		T[num - 1] = min;
	}

	return T[n-1];
}

int main(void) {
	long n; // 1 <= n <= 10^3
	scanf("%ld", &n);

	printf("%ld", calc(n));

	return 0;
}

