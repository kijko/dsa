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

long long apply_operation(char op, long long a, long long b) {
	if (op == '+') {
		return a + b;
	} else if (op == '-') {
		return a - b;
	} else {
		return a * b;
	}
}

void min_max(int n, long long m[][n], long long M[][n], int i, int j, char *op) {
	long long min = LONG_MAX, max = LONG_MIN;

	long long r[4];
	for (int k = i; k <= j - 1; k++) {
		r[0] = apply_operation(op[k-1], M[i-1][k-1], M[(k-1)+1][j-1]);
		r[1] = apply_operation(op[k-1], M[i-1][k-1], m[(k-1)+1][j-1]);
		r[2] = apply_operation(op[k-1], m[i-1][k-1], M[(k-1)+1][j-1]);
		r[3] = apply_operation(op[k-1], m[i-1][k-1], m[(k-1)+1][j-1]);

		for (int ir = 0; ir < 4; ir++) {
			if (r[ir] < min) min = r[ir];
			if (r[ir] > max) max = r[ir];	
		}
	}
	
	m[i-1][j-1] = min;
	M[i-1][j-1] = max;
}

long long max(int *d, int n, char *op, int k) {
	long long M[n][n], m[n][n];

//	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) { M[i][j] = 0; m[i][j] = 0; }

	for (int i = 0; i < n; i++) {
		M[i][i] = (long long) d[i];
		m[i][i] = (long long) d[i];
	}

	int j = 0;
	for (int s = 1; s <= n - 1; s++) {
		for (int i = 1; i <= n - s; i++) {
			j = i + s;
			min_max(n, m, M, i, j, op);
		}
	}
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			printf("%d ", M[i][j]);
//		}
//		printf("\n");
//	}
//
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			printf("%d ", m[i][j]);
//		}
//		printf("\n");
//	}

	return M[0][n-1];
}

// https://stackoverflow.com/questions/56196926/algorithmic-toolbox-maximize-arithmetic-expression-using-parentheses-failed-t
int main(void) {
	int sLen = 0;
	char s[100];
	scanf("%s", s);

	for (int i = 0; i < 100; i++) if (s[i] != '\0') sLen++; else break;
	
	if (sLen == 0) {
		printf("000");
	}
	
	int n = (sLen / 2) + 1, k = (sLen / 2);
	int d[n], i1 = 0, i2 = 0;
	char op[k];
	for (int i = 0; i < sLen; i++) {
		if (i % 2 == 0) {
			d[i1] = s[i] - '0';
			i1++;
		} else {
			op[i2] = s[i];
			i2++;
		}
	}

	
//	for (int i = 0; i < n; i++) printf("%d ", d[i]);
//	printf("\n");
//	for (int i = 0; i < k; i++) printf("%c", op[i]);
//	printf("\n");
//	printf("digits: %d, operations: %d", n, k);

	printf("%lld", max(d, n, op, k));

	return 0;
}

