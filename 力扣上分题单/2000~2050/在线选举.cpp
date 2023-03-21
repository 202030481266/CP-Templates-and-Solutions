// https://leetcode.cn/problems/online-election/



class TopVotedCandidate {
public:
	vector<int> a, b, ans;
	unordered_map<int, pair<int, int>> h;
	set<tuple<int, int, int>> s;

    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
		a = persons;
		b = times;
		ans.resize(times.size());

		int n = b.size();

		for (int i = 0; i < n; ++i) {
			int p = a[i];
			if (h.count(p)) {
				auto [ticks, latest] = h[p];
				s.erase(s.find(tuple<int, int, int>{ticks, latest, p}));
				h[p] = make_pair(ticks + 1, b[i]);
				s.emplace(tuple<int, int, int>{ticks + 1, b[i], p});
			}
			else {
				h[p] = make_pair(1, b[i]);
				s.emplace(tuple<int, int, int>{1, b[i], p});
			}
			ans[i] = get<2>(*s.rbegin());
		}
    }

    int q(int t) {
		auto it = lower_bound(b.begin(), b.end(), t);
		if (it == b.end()) {
			return ans.back();
		}
		int pos = it - b.begin();
		if (*it == t) {
			return ans[pos];
		}
		else return ans[pos - 1];
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */