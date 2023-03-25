#include <bits/stdc++.h>
using namespace std;

// find 9 numbers at different row and col and room
// the all numbers should not be previous value
// so a simple solution is find all the '1', and replace it as '2'


// 规律题目，考虑贪心替换

void solve() {
	for (int i = 1; i <= 9; ++i) {
		string t;
		cin >> t;
		for (int j = 0; j < 9; ++j)
			if (t[j] == '1') t[j] == '2';
		cout << t << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
}