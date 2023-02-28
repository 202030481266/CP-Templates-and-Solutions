// https://leetcode.cn/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/
// 每一次都尽量缩小这样可以保证每一步是最优的


class Solution {
public:
    int findMinFibonacciNumbers(int k) {
    	long long n = 1ll * k;
    	vector<long long> arr(51);

    	arr[0] = arr[1] = 1;
    	for (int i = 2; i <= 50; ++i)
    		arr[i] = arr[i - 1] + arr[i - 2];

    	int ans = 0;
    	function<void(long long)> dfs = [&](long long N) {
    		if (N == 0) return;
    		int t = lower_bound(arr.begin(), arr.end(), N) - arr.begin();
    		if (arr[t] == N) {
    			++ans;
    		}
    		else {
    			++ans;
    			dfs(N - arr[t - 1]);
    		}
    	};
    	dfs(n);
    	return ans;
    }
};