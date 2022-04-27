#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//int max(long l1, long l2) {
//	return l1 > l2 ? l1 : (l1 < l2 ? l2 : l1);
//}

long calc(long W, long *v, long n) {
	long **R = calloc(W+1, sizeof(long));
	for (long i = 0; i <= W; i++) R[i] = calloc(n+1, sizeof(long));

	//long R[W+1][n+1];
	
	for (long i = 0; i <= W; i++) R[i][0] = 0;
	for (long i = 0; i <= n; i++) R[0][i] = 0;

	long lastCurrElem, val;
	for (long i = 1; i <= n; i++) {
		for (long sW = 1; sW <= W; sW++) {
			R[sW][i] = R[sW][i-1];
			lastCurrElem = v[i-1];
			if (lastCurrElem <= sW) {
				val = R[sW - lastCurrElem][i - 1] + lastCurrElem;
				if (val > R[sW][i]) {
					R[sW][i] = val;
				}
			}
		}
	}

	long result = R[W][n];
	
	for (long i = 0; i <= W; i++) {
		free(R[i]);
	}
	free(R);

	return result;
}

// todo segmentation fault for max W and max n. Limit of dynamic array on stack...
int main(void) {
	long W, n; // 1 <= W <= 10^4 & 1 <= n <= 300 
	scanf("%ld %ld", &W, &n);

	long v[n];
	for (int i = 0; i < n; i++) scanf("%ld", &v[i]);


	printf("%ld", calc(W, v, n));

	return 0;
}

