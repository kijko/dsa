#include <stdio.h>
#include <stdbool.h>


double calcloot(int n, double W, long int* values, long int* weights) {
	double V = 0;

	// setup ratio array
	double ratio[n], value, weight;
	for (int i = 0; i < n; i++) {
		value = (double) values[i];
		weight = (double) weights[i];
		ratio[i] = value / weight;
	}

	// setup taken array
	bool taken[n];
	for (int i = 0; i < n; i++) {
		taken[i] = false;
	}

	// loot
	double max_ratio, amount;
	int max_ratio_index;
	while (W > 0) {
		max_ratio = -1;
		max_ratio_index = -1;
		for (int i = 0; i < n; i++) {
			if (ratio[i] >= max_ratio && !taken[i]) {
				max_ratio = ratio[i];
				max_ratio_index = i;
			}
		}

		amount = 0;
		if (W <= weights[max_ratio_index]) {
			amount = ((double) W) / ((double) weights[max_ratio_index]);
		} else {
			amount = 1;
		}

		V += amount * values[max_ratio_index];
		W -= amount * weights[max_ratio_index];
		taken[max_ratio_index] = true;
	}


	return V;

}

int main(void) {
	int n; // 1 <= n <= 10^3
	double W; // 0 <= W <= 2 * 10^6
	scanf("%d %lf", &n, &W);

	long int values[n];
	long int weights[n];
	for (int i = 0; i < n; i++) {
		scanf("%ld %ld", &values[i], &weights[i]);
	}

	printf("%.4lf", calcloot(n, W, values, weights));

	return 0;
}

