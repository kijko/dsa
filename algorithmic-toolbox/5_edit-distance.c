#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int calc(char *s1, int lenS1, char *s2, int lenS2) {
	int T[lenS1 + 1][lenS2 + 1], prev[3];
	char a, b;

	for (int i = 0; i < lenS1 + 1; i++)
		T[i][0] = i;

	for (int i = 0; i < lenS2 + 1; i++)
		T[0][i] = i;

	for (int i = 1; i < lenS2 + 1; i++) {
		for (int j = 1; j < lenS1 + 1; j++) {
			a = s1[j - 1];
			b = s2[i - 1];

			if (a == b) {
				T[j][i] = T[j - 1][i - 1];
			} else {
				prev[0] = T[j - 1][i];
				prev[1] = T[j][i - 1];
				prev[2] = T[j - 1][i - 1];

				T[j][i] = prev[0];
				for (int p = 1; p < 3; p++) {
					if (prev[p] < T[j][i]) T[j][i] = prev[p];
				}
				T[j][i]++;
			}
		}
	}

//	for (int i = 0; i < lenS1 + 1; i++) {
//		for (int j = 0; j < lenS2 + 1; j++) {
//			printf("%d", T[i][j]);
//		}
//		printf("\n");
//	}

	return T[lenS1][lenS2];
}

int main(void) {
	int lenS1 = 0, lenS2 = 0;
	char s1[100], s2[100];
	scanf("%s", s1);
	scanf("%s", s2);

	for (int i = 0; i < 100; i++) if (s1[i] != '\0') lenS1++; else break;
	for (int i = 0; i < 100; i++) if (s2[i] != '\0') lenS2++; else break;

	printf("%d", calc(s1, lenS1, s2, lenS2));

	return 0;
}

