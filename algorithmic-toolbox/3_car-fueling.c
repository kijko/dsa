#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int find_farest_point(int* stop, short n, short m, int position, int d) {
	int farest_point = -1;
	int pos_and_fuel = position + ((int) m);

	if (d <= pos_and_fuel) {
		return d;
	}


	for (int i = 0; i < n; i++) {
		if (stop[i] <= pos_and_fuel) {
			farest_point = stop[i];
		}
	}

	if (farest_point == position) {
		return -1;
	} else {
		return farest_point;
	}
}

short calc_fueling(int d, short m, short n, int * stop) {
	short stop_count = 0;
	int position = 0;
	
	while (position < d) {
//		printf("debug [position=%d, d=%d]\n", position, d);
		int farest_point = find_farest_point(stop, n, m, position, d);
//		printf("debug [farest_point=%d]\n",farest_point);
		if (farest_point == -1) {
			return -1;
		} else {
			position = farest_point;
			if (position < d) {
				stop_count++;
			}
		}
	}
	
	return stop_count;
}

int main(void) {
	int d; scanf("%d", &d); // 1 <= d <= 10^5
	short m, n; scanf("%hd", &m); scanf("%hd", &n); // 1 <= n <= 300 <= m <= 400
	int stop[n]; // 0 < stop[i] < d

	for (int i = 0; i < n; i++) scanf("%d", &stop[i]);

	printf("%hd", calc_fueling(d, m, n, stop));

	return 0;
}

