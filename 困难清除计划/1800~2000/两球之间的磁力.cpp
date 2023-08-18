// https://leetcode.cn/problems/magnetic-force-between-two-balls/



class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
    	int n = position.size();

    	sort(position.begin(), position.end());
    	int l = 1, r = 1000000000;

    	auto f = [&](int v) {
    		int p = 1, cnt = 1, last = position[0];
    		while (p < n) {
    			while (p < n && position[p] < last + v) ++p;
    			if (p != n) {
    				++cnt;
    				last = position[p];
    			}
    		}
    		return cnt >= m;
    	};

    	int ans = 1;
    	while (l <= r) {
    		int mid = (l + r) >> 1;
    		if (f(mid)) {
    			ans = mid;
    			l = mid + 1;
    		}
    		else r = mid - 1;
    	}
    	return ans;
    }
};