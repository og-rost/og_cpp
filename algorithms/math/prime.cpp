/***************************************************/

bool isPrime(int n) {
	for (int i = 2; i <= sqrt(n); ++i) {
		if (n % i == 0)
			return false;
	}
	return true;
}

/***************************************************/

int nthPrime(int n) {
	int prime = 0;
	int count = 0;
	for (int i = 2; count < n; ++i)	{
		if(isPrime(i)) {
			++count;
			prime = i;
		}
	}
	return prime;
}
