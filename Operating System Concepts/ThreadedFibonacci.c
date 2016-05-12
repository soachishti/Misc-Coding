#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int fib(int* n) {
	if (n <= 0) return 0;
	else if (n == 1) return 1;
	else {
		pthread_t t1, t2;
		pthread_create(&t1, NULL, fib, n-1);
		pthread_create(&t2, NULL, fib, n-2);

		int ret1,ret2;
		pthread_join(t1, &ret1);
		pthread_join(t2, &ret2);	
	
		return ret1+ret2;
	}
}

int main() {
	int val = 5;
	int result = fib(val);
	printf("%d\n\n", result);
	return 0;
}

