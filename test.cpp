#include <bits/stdc++.h>
using namespace std;

void print(vector<int>& a) {
	int n = a.size(), dp[n];
	for (int i = 0; i < n; ++i) {
		dp[i] = a[i];
		cout << dp[i] << ' ';
	}
	cout << endl;
}


int main() {
	vector<int> arr{1, 2, 3};
	print(arr);
	return 0;
}
