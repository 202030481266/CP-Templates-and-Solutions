// xiaoshulin
// 2024.1.1

class Solution {
public:
    int circleGame(vector<vector<int>>& toys, vector<vector<int>>& circles, int r) {
		int n = toys.size(), m = circles.size(), ans = 0;
		const int offset = 1e9; 
		vector<int> a;
		for (auto& t : toys) a.push_back(t[0]);
		sort(a.begin(), a.end());
		a.erase(unique(a.begin(), a.end()), a.end());
		vector<set<int>> s(a.size());
		unordered_map<long long, int> radius;
		for (auto& t : toys) {
			radius[1ll * t[0] * offset + t[1]] = t[2];
			int index = lower_bound(a.begin(), a.end(), t[0]) - a.begin();
			s[index].insert(t[1]);
		}
		for (auto& c : circles) {
			auto index = lower_bound(a.begin(), a.end(), c[0] - r);
			if (index != a.end()) {
				for (int i = index - a.begin(); i < a.size() && a[i] <= c[0] + r; ++i) {
					for (auto it = s[i].lower_bound(c[1] - r); it != s[i].end(); ) {
						int R = radius[1ll * a[i] * offset + *it];
						if (r < R) {
							++it;
						}
						else if (*it > c[1] + r) {
							break;
						}
						else if (1ll * (c[1] - *it) * (c[1] - *it) + 1ll * (c[0] - a[i]) * (c[0] - a[i]) > 1ll * (R - r) * (R - r)) {
							++it;
						}
						else {
							++ans;
							it = s[i].erase(it);
						}
					}
				}
			}
		}
		return ans;
    }
};
