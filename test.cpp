#include <iostream>
using namespace std;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	int t;
	cin >> t;
	while (t--) {
		int x, y;
		cin >> x >> y;
		solve(x, y);
	}
	return 0;
}
