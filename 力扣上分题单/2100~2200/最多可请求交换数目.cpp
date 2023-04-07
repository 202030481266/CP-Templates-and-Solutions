// https://leetcode.cn/problems/maximum-number-of-achievable-transfer-requests/




class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
    	int m = requests.size();
    	int ans = 0;

    	vector<int> in(n), out(n);
    	vector<vector<int>> edges;

    	for (auto c : requests) {
    		if (c[1] == c[0]) ++ans;
    		else edges.emplace_back(c);
    	}

    	int N = edges.size();

    	auto f = [&](int v) -> int {
    		fill(in.begin(), in.end(), 0);
    		fill(out.begin(), out.end(), 0);
    		int k = 0;
    		for (int i = 0; i < N; ++i) {
    			if ((v >> i) & 1) {
    				++k;
    				++out[edges[i][0]];
    				++in[edges[i][1]];
    			}
    		}
    		bool flag = true;
    		for (int i = 0; i < n; ++i) {
    			if (in[i] != out[i]) {
    				flag = false;
    				break;
    			}
    		}
    		if (flag) return k;
    		else return -1;
    	};

    	// 暴力搜索
    	int res = 0;
    	for (int i = 0; i < (1 << N); ++i) {
    		int tmp = f(i);
    		if (tmp != -1) res = max(res, tmp);
    	}
    	return ans + res;
    }
};