#include <stdio.h>
#include <stdbool.h>

int change(int m) {
	int coins[3] = {10, 5, 1};
	int count = 0;

	while (m > 0) {
		for (int i = 0; i < sizeof(coins); i++) {
			if (m >= coins[i]) {
				m = m - coins[i];
				count++;
				break;
			}
		}
	}

	return count;
}

int main(void) {
	int m; // 1 <= m <= 10^3
	scanf("%d", &m);

	printf("%d", change(m));

	return 0;
}

