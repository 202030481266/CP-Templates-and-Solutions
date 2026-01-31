const long long[] num = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600};

long long cantorExpansion(const vector<int>& a) {
	long long res = 0;
	int n = a.size();
	for (int i = 0; i < n; ++i) {
		int smaller = 0;
		for (int j = i + 1; j < n; ++j)
			if (a[j] < a[i]) ++smaller;
		res += smaller * num[n - i - 1];
	}
	return res;
}
vector<int> reverseCantorExpansion(long long hash, int length) {
	vector<int> permutation;
	vector<int> available(length);

	iota(available.begin(), available.end(), 0);
	for (int i = 0; i < length; ++i) {
		int weight = hash / num[length - i - 1];
		int digit = available[weight];
		permutation.push_back(digit);
		available.erase(available.begin() + weight);
		hash %= num[length - i - 1];
	}

	return permutation;
}