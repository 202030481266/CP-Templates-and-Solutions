#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

using ll = long long;

int arr[3][100005];
static constexpr int pos[3][2] = { {1, 2}, {0, 2}, {0, 1} };

void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < n; ++j) cin >> arr[i][j];
	}
	auto cal = [&](int r) -> array<int, 6> {
		array<int, 6> res = { 0, 0, 0, 0, 0, 0 };
		for (int i = 0; i < n; ++i) {
			if (arr[r][i] > res[0]) {
				res[2] = res[1]; 
				res[5] = res[4];
				res[1] = res[0];
				res[4] = res[3];
				res[0] = arr[r][i];
				res[3] = i;
			}
			else if (arr[r][i] > res[1]) {
				res[2] = res[1];
				res[5] = res[4];
				res[1] = arr[r][i];
				res[4] = i;
			}
			else if (arr[r][i] > res[2]) {
				res[2] = arr[r][i];
				res[5] = i;
			}
		}
		return res;
	};
	vector<array<int, 6>> res(3);
	for (int i = 0; i < 3; ++i) res[i] = cal(i);
	int ans = 0;
	auto sol1 = [&](int x) -> void {
		int y = pos[x][0], z = pos[x][1];
		if (res[y][4] != res[z][4]) ans = max(ans, res[x][0] + res[y][1] + res[z][1]);
		else ans = max(ans, res[x][0] + max(res[y][1] + res[z][2], res[y][2] + res[z][1]));
	};
	auto sol2 = [&](int x, int y) -> void {
		int z = 3 - x - y;
		// z takes max
		if (res[x][4] != res[z][3]) ans = max(ans, res[x][1] + res[y][0] + res[z][0]);
		else ans = max(ans, res[x][2] + res[y][0] + res[z][0]);
		if (res[y][4] != res[z][3]) ans = max(ans, res[y][1] + res[x][0] + res[z][0]);
		else ans = max(ans, res[y][2] + res[x][0] + res[z][0]);
		// z not takes max
		if (res[x][4] == res[z][3]) {
			if (res[z][4] != res[y][3]) ans = max(ans, res[x][1] + res[y][0] + res[z][1]);
			else ans = max(ans, res[x][1] + res[y][0] + res[z][2]);
		}
		if (res[y][4] == res[z][3]) {
			if (res[z][4] != res[x][3]) ans = max(ans, res[x][0] + res[y][1] + res[z][1]);
			else ans = max(ans, res[x][0] + res[y][1] + res[z][2]);
		}
	};
	if (res[0][3] != res[1][3] && res[0][3] != res[2][3] && res[1][3] != res[2][3]) {
		cout << res[0][0] + res[1][0] + res[2][0] << '\n';
		return;
	}
	if (res[0][3] == res[1][3] && res[0][3] == res[2][3]) {
		for (int i = 0; i < 3; ++i) sol1(i);
		cout << ans << '\n';
		return;
	}
	if (res[0][3] == res[1][3]) sol2(0, 1);
	if (res[0][3] == res[2][3]) sol2(0, 2);
	if (res[1][3] == res[2][3]) sol2(1, 2);
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}