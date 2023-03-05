// https://leetcode.cn/problems/maximum-number-of-removable-characters/



class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
    	int n = removable.size();
    	int N = s.size(), M = p.size();

    	int l = 0, r = n;

    	auto f = [&](int k) {
    		string t = s;
    		for (int i = 0; i < k; ++i) 
    			t[removable[i]] = '1';
    		int x = 0, y = 0;
    		while (x < N && y < M) {
    			if (t[x] == p[y])
    				++y;
    			++x;
    		}
    		return y == M;
    	};


    	int ans = 0;
    	while (l <= r) {
    		int mid = (l + r) >> 1;
    		if (f(mid))
    			ans = mid, l = mid + 1;
    		else r = mid - 1;
    	}

    	return ans;
    }
};