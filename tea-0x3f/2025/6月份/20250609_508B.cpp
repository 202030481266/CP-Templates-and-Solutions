// https://codeforces.com/problemset/problem/508/B
#include <bits/stdc++.h>
using namespace std;

string s;

void cf508B() {
	cin >> s;
	int n = s.size(), flag = 0, pre = -1;
	for (int i = 0; i < n - 1; ++i) {
		if ((s[i] - '0') % 2 == 0) {
			if (s[i] < s[n - 1]) {
				swap(s[i], s[n - 1]);
				flag = 1;
				break;
			}
			else {
				pre = i;
			}
		}
	}
	if (flag) cout << s << '\n';
	else {
		if (pre == -1) cout << -1 << endl;
		else {
			swap(s[pre], s[n - 1]);
			cout << s << '\n';
		}
	}
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cf508B();
}
