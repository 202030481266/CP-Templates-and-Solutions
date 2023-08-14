class Solution {
public:
	int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
		int n = tasks.size(), m = workers.size(), ans = 0;
		sort(tasks.begin(), tasks.end());
		sort(workers.begin(), workers.end());
		auto f = [&](int k) -> bool {
			multiset<int> s;
			int p = pills;
			for (int i = m - k; i < m; ++i) s.emplace(workers[i]);
			for (int i = k - 1; i >= 0; --i) {
				auto it = s.lower_bound(tasks[i]);
				if (it != s.end()) {
					s.erase(it);
					continue;
				}
				if (p) {
					auto it = s.lower_bound(tasks[i] - strength);
					if (it != s.end()) {
						s.erase(it);
						--p;
						continue;
					}
				}
				return false;
			}
            return true;
		};
		int l = 1, r = min(m, n);
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (f(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		return ans;
	}
};
