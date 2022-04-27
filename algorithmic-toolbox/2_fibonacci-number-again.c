#include <stdio.h>
#include <stdbool.h>

long long fibo(int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else if (n == 2) {
		return 1;
	}

	unsigned long long memory[n+1];
	memory[0]=0;
	memory[1]=1;
	memory[2]=1;

	int i;
	for (i = 3; i <= n; i++) {
		memory[i]=memory[i-1] + memory[i-2];
	}


	return memory[n];
}

long calculatePisanoPeriod(long m){
    long previous = 0, current = 1, result = 0, temp = 0;
 
    for(long i = 0; i < m * m; i++) {
        temp = current;
        current = (previous + current) % m;
        previous = temp;
 
        if (previous == 0 && current == 1) {
            result = i + 1;
	}
    }
    return result;
}

long fiboMod(long long n, long m) {
    long pisanoPeriod = calculatePisanoPeriod(m);
 
    n = n % pisanoPeriod;
 
    long prev = 0;
    long curr = 1;
 
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
 
    for(long long i = 0; i < n - 1; i++) {
        long temp = 0;
        temp = curr;
        curr = (prev + curr) % m;
        prev = temp;
    }
    return curr % m;
}

int main(void) {
	long long int n; // 1 <= n <= 10^14
	long m; // 2 <= m <= 10^3
	scanf("%lld", &n);
	scanf("%ld", &m);

	long result = fiboMod(n, m);
	printf("%ld", result);

	return 0;
}

