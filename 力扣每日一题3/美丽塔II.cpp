// xiaoshulin
// 2023.12.21

class Solution {
public:
    long long maximumSumOfHeights(vector<int>& heights) {
		int n = h.size();
		vector<long long> h(heights.begin(), heights.end());
		vector<int> pre(n, -1), suf(n, n);
		vector<long long> f(n), g(n);
		stack<int> s;
		for (int i = 0; i < n; ++i) {
			while (!s.empty() && h[s.top()] >= h[i]) {
				suf[s.top()] = i;
				s.pop();
			}
			s.push(i);
		}
		s = stack<int>{};
		for (int i = n - 1; i >= 0; --i) {
			while (!s.empty() && h[s.top()] >= h[i]) {
				pre[s.top()] = i;
				s.pop();
			}
			s.push(i);
		}
		for (int i = 0; i < n; ++i) {
			int p = pre[i];
			if (p >= 0) {
				// (p, i]
				f[i] = f[p] + (i - p) * h[i];
			}
			else {
				f[i] = h[i] * (i + 1);
			}
		}
		long long ans = 0;
		for (int i = n - 1; i >= 0; --i) {
			int p = suf[i];
			if (p < n) {
				// [i, p)
				g[i] = g[p] + (p - i) * h[i];
			}
			else {
				g[i] = h[i] * (n - i);
			}
			ans = max(ans, f[i] + g[i] - h[i]);
		}
		return ans;
    }
};
