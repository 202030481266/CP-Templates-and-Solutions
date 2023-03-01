// https://leetcode.cn/problems/jump-game-v/



template<typename T>
struct ST {
	// index start from 0
	int N;
	vector<vector<T>> vec;

	ST() { N = 0; }
	ST(int n) {
		N = n;
		vec.resize(N);
		for (auto& v : vec) v = vector<T>(30, 0);
		for (int i = 0; i < N; i++) {
			cin >> vec[i][0];
		}
	}
	ST(const vector<T>& a) {
		vec.resize(a.size());
		N = a.size();
		for (auto& v : vec) v = vector<T>(30, 0);
		for (int i = 0; i < N; i++) vec[i][0] = a[i];
	}
	void ST_work() {
		int t = log(N) / log(2) + 1;
		for (int i = 1; i < t; i++) {
			for (int j = 0; j + (1 << i) - 1 < N; j++) {
				vec[j][i] = max(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
	void ST_debug() {
		// 打印调试ST表
		int t = log(N) / log(2) + 1;
		for (int i = 0; i < t; i++) {
			cout << "the length of step is " << (1 << i) << endl;
			for (int j = 0; j + (1 << i) - 1 < N; j++) {
				cout << "now on start from index " << j << ' ';
				cout << "value is " << vec[j][i] << endl;
			}
		}
	}
	T query(int l, int r) {
		int k = log(r - l + 1) / log(2);
		return max(vec[l][k], vec[r - (1 << k) + 1][k]);
	}
	int lower_bound(int l, int r, T val) {
		// first position k that max{l,.....,k} >= val
		int start = l, res = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			T temp = query(start, mid);
			if (temp >= val) res = mid, r = mid - 1;
			else l = mid + 1;
		}
		return res;
	}
};


class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
    	int n = arr.size();

    	ST<int> st(arr);
    	st.ST_work();

    	vector<int> dp(n, -1);

    	function<int(int)> dfs = [&](int p) -> int {
    		if (dp[p] != -1) return dp[p];

    		int maxx = INT_MIN;
    		for (int i = max(0, p - d); i <= min(n - 1, p + d); ++i) {
    			if (i == p) continue;
    			if (arr[p] <= arr[i]) continue;
    			int l = min(p, i), r = max(p, i);
    			if (r - l > 1) {
					int t = st.query(l + 1, r - 1);
	    			if (t < arr[p]) {
	    				maxx = max(maxx, dfs(i) + 1);
	    			}
    			}
    			else maxx = max(maxx, dfs(i) + 1);
    			
    		}

    		if (maxx == INT_MIN) dp[p] = 0;
            else dp[p] = maxx;
            return dp[p];
    	};

    	for (int i = 0; i < n; ++i)
    		if (dp[i] == -1) dfs(i);
    	int ans = INT_MIN;
    	for (int i = 0; i < n; ++i) {
    		// cout << dp[i] << ' ';
            ans = max(ans, dp[i]);
        }
    	return ans + 1;
    }
};