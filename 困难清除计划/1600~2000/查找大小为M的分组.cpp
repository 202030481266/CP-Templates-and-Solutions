// https://leetcode.cn/problems/find-latest-group-of-size-m/



class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
    	int n = arr.size();
    	unordered_map<int, pair<int, int>> intervals;
    	vector<int> st(n + 2);
    	vector<int> ed(n + 2);
    	vector<int> cnt(n + 2);

    	int idx = 0;
    	int ans = -1;
    	for (int i = 0; i < n; ++i) {
    		// try find the pre interval
    		int pos = arr[i];
    		if (ed[pos - 1] > 0 && st[pos + 1] > 0) {
    			// means can be merge at left and right point
    			int left = ed[pos - 1], right = st[pos + 1];
    			auto l = intervals[left];
    			auto r = intervals[right];
    			// delete the pre status;
    			--cnt[l.second - l.first + 1];
    			--cnt[r.second - r.first + 1];
    			intervals.erase(left);
    			intervals.erase(right);
    			st[l.first] = st[r.first] = 0;
    			ed[l.second] = ed[r.second] = 0;
    			// add new status
    			int new_idx = ++idx;
    			st[l.first] = ed[r.second] = new_idx;
    			++cnt[r.second - l.first + 1];
    			intervals[new_idx] = make_pair(l.first, r.second);
    		}
    		else if (ed[pos - 1] > 0) {
    			int left = ed[pos - 1];
    			auto l = intervals[left];
    			--cnt[l.second - l.first + 1];
    			++cnt[pos - l.first + 1];
    			ed[pos - 1] = 0;
    			ed[pos] = left;
    			intervals[left] = make_pair(l.first, pos);
    		}
    		else if (st[pos + 1] > 0) {
    			int right = st[pos + 1];
    			auto r = intervals[right];
    			--cnt[r.second - r.first + 1];
    			++cnt[r.second - pos + 1];
    			st[pos + 1] = 0;
    			st[pos] = right;
    			intervals[right] = make_pair(pos, r.second);
    		}
    		else {
    			// no merge
    			int new_idx = ++idx;
    			intervals[new_idx] = make_pair(pos, pos);
    			st[pos] = ed[pos] = new_idx;
    			++cnt[1];
    		}
    		if (cnt[m] > 0) ans = i + 1;
    	}
    	return ans;
    }
};