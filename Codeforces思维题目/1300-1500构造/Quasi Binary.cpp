// greedy

#include <bits/stdc++.h>
using namespace std;

const int p10[] = {1, 10, 100, 1000, 10'000, 100'000, 1'000'000, 10'000'000};

int main() {
	int n;
	cin >> n;
	vector<int> a;
	while (n) {
		a.push_back(n % 10);
		n /= 10;
	}
	n = a.size();
	vector<pair<int, int>> ans;
	int res = 0;
	while (true) {
		int mn = INT_MAX, sum = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] > 0) {
				mn = min(mn, a[i]);
			}
		}
		if (mn == INT_MAX) break;
		for (int i = 0; i < n; ++i) {
			if (a[i] > 0) {
				sum += p10[i];
				a[i] -= mn;
			}
		}
		ans.push_back({mn, sum});
		res += mn;
	}
	cout << res << endl;
	for (auto& p : ans) {
		for (int i = 0; i < p.first; ++i)
			cout << p.second << ' ';
	}
	return 0;
}