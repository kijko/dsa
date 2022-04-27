#include <stdio.h>
#include <stdbool.h>

int search(int elem, int *arr, short down, short up) {
	if (down > up || up < down) return -1;

	short middle = (down + up) / 2;

	if (arr[middle] == elem) {
		return middle;
	} else if (arr[middle] < elem) {
		return search(elem, arr, middle + 1, up);
	} else if (arr[middle] > elem) {
		return search(elem, arr, down, middle - 1);
	}

}

int searchIterative(int elem, int *arr, int n) {
	int down = 0, up = n - 1;
	int result = -1;
	
	while (down <= up) {
		int middle = (down + up) / 2;
		if (arr[middle] == elem) {
			result = middle;
			break;
		} else if (arr[middle] < elem) {
			down = middle + 1;
		} else if (arr[middle] > elem) {
			up = middle - 1;
		}
	}

	return result;
}

void binary_search(int n, int *arr, int k, int *in, int *out) {
	int elem, result;
	for (int i = 0; i < k; i++) {
		elem = in[i];
//		printf("elem=%d - ", elem);
//		out[i] = search(elem, arr, 0, n - 1);
		result = searchIterative(elem, arr, n);

		while (result > 0 && arr[result-1] == arr[result]) {
			result--;
		}

		out[i] = result;
//		printf("found=%d\n", out[i]);
	}
}

int main(void) {
	int n, k; // 1 <= n <= 3 * 10^4
	scanf("%d", &n);
	int arr[n];
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	
	scanf("%d", &k);
	int in[k];
	for (int i = 0; i < k; i++) scanf("%d", &in[i]);

	int out[k];
        binary_search(n, arr, k, in, out);

	for (int i = 0; i < k; i++) printf("%d ", out[i]);

	return 0;
}

