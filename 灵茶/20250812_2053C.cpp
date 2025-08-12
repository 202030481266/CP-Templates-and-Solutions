#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

void solve() {
	uint n, k;
	cin >> n >> k;
	int a = bit_width(n), b = bit_width(k), diff = a - b;
	if ((n >> diff) >= k) ++diff;
	ull x = ((1u << diff) - 1) & n;
	cout << (1u + n) * x / 2 << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve(); 
}