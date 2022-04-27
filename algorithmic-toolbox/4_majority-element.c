#include <stdio.h>
#include <stdbool.h>

int count(long long elem, int d, int u, long long *arr) {
	int result = 0;

	for (int i = d; i <= u; i++) {
		if (arr[i] == elem) {
			result++;
		}
	}

	return result;
}

long long get_majority_elem(int d, int u, long long *arr) {
	int n = u - d + 1, mid = -1, cm1 = 0, cm2 = 0;
	long long m1 = -1, m2 = -1;

	if (n == 1) {
		//printf("n == 1 - return %lld\n", arr[u]);
		return arr[u];
	} else if (n == 2) {
		if (arr[d] == arr[u]) {
			//printf("n == 2 - return %lld\n", arr[u]);
			return arr[u];
		} else {
			//printf("n == 2 - return %d\n", -1);
			return -1;
		}
	} else {
		mid = (d + u) / 2;
		//printf("mid = %d\n", mid);
		m1 = get_majority_elem(d, mid, arr);
		//printf("m1 = %lld\n", m1);

		cm1 = count(m1, d, u, arr);
		//printf("cm1 = %d\n", cm1);
		if (cm1 > n/2) {
			//printf("n/2=%d returning %lld\n", n/2, m1);
			return m1;
		}

		m2 = get_majority_elem(mid + 1, u, arr);
		//printf("m2 = %lld\n", m2);
		cm2 = count(m2, d, u, arr);
		//printf("cm2 = %d\n", cm2);
		if (cm2 > n/2) {
			//printf("n/2=%d returning %lld\n", n/2, m2);
			return m2;
		}

		//printf("n/2=%d returning %d\n", n/2, -1);
		return -1;
	}

}

// todo 1 1 1 3 3 3 3 3 5 5 fails
int main(void) {
	int n; // 1 <= n <= 10^5
	scanf("%d", &n);
	long long arr[n];
	for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);

	long long majority_elem = get_majority_elem(0, n - 1, arr);
	//printf("majority elem %lld\n", majority_elem);
	
	if (majority_elem > -1) {
		printf("1");
	} else {
		printf("0");
	}

	return 0;
}

