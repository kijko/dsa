#include <stdio.h>
  
long long maxPairwiseProd(int n, int nums[]) {
	int i, max1 = -1, max1Index = -1, max2 = -1, max2Index = -1;
	for (i = 0; i < n; i++) {
		if (nums[i] > max1) {
			max1 = nums[i];
			max1Index = i;
		}
	}

	for (i = 0; i < n; i++) {
		if (nums[i] > max2 && i != max1Index) {
			max2 = nums[i];
			max2Index = i;
		}
	}

	return ((long long) max1) * ((long long) max2);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int i;
    int nums[n];
    for (i = 0; i < n; i++) {
	    scanf("%d", &nums[i]);
    }

    printf("%lld", maxPairwiseProd(n, nums));
  
    return 0;
}


