#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void calc(long n) {
	int T[n][4];
	long num, a, m2, m3;
	int ar, m2r, m3r, min;

	for (int i = n-1; i >= 0; i--) {
		num = i + 1;
		if (num == n) {
			T[i][0] = 0;
			T[i][1] = 0;
			T[i][2] = 0;
			T[i][3] = 0;
			continue;
		} else {
			a = num + 1;
			if (a == n) {
				ar = 1;
			} else { // a < n
				ar = T[a-1][0] + 1;
			}

			m2 = num * 2;
			if (m2 == n) {
				m2r = 1;
			} else if (m2 > n) {
				m2r = -1;
			} else { // m2 < n
				m2r = T[m2 - 1][0] + 1;
			}

			m3 = num * 3;
			if (m3 == n) {
				m3r = 1;
			} else if (m3 > n) {
				m3r = -1;
			} else { // m3 < n
				m3r = T[m3 - 1][0] + 1;
			}

			min = INT_MAX;
			if (ar < min && ar != -1) min = ar;
			if (m2r < min && m2r != -1) min = m2r;
			if (m3r < min && m3r != -1) min = m3r;

			T[i][0] = min;
			T[i][1] = ar;
			T[i][2] = m2r;
			T[i][3] = m3r;
		}

	}

	long S[T[0][0] + 1];
	S[0] = 1;
	S[T[0][0] + 1] = n;
	for (int i = 1; i < (T[0][0] + 1); i++) {
		num = S[i - 1];

		min = T[num - 1][0];
		ar = T[num - 1][1];
		m2r = T[num - 1][2];
		m3r = T[num - 1][3];
		if (ar == min) {
			S[i] = S[i - 1] + 1;
		} else if (m2r == min) {
			S[i] = S[i - 1]*2;
		} else if (m3r == min) {
			S[i] = S[i - 1]*3;
		}
	}
	

	printf("%d\n", T[0][0]);
	for (int i = 0; i < T[0][0] + 1; i++) {
		if (S[i] != -1) {
			printf("%ld ", S[i]);
		}
	}

}

int main(void) {
	long n; // 1 <= n <= 10^6
	scanf("%ld", &n);

	calc(n);

	return 0;
}

