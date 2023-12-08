#include <iostream>
using namespace std;




int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int t;
	cin >> t;
	while (t--) {
		int x, y;
		cin >> x >> y;
		if (solve(x, y)) cout << solve(x, y) << '\n';
		else cout << -1 << end;
	}
	return 0;
}
