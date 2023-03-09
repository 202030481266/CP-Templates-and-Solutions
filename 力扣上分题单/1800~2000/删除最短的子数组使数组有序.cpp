// https://leetcode.cn/problems/shortest-subarray-to-be-removed-to-make-array-sorted/



class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
    	int n = arr.size();

    	vector<int> f(n + 1);

    	f[n - 1] = n - 1;
    	for (int i = n - 2; i >= 0; --i) {
    		if (arr[i] <= arr[i + 1]) f[i] = f[i + 1];
    		else f[i] = i;
    	}
    	int ans = INT_MAX;
    	int pos = -1;
    	for (int i = n - 1; i >= 0; --i) {
    		if (f[i] != n - 1) {
    			// 0~i
    			pos = i;
    			break;
    		}
    	}
    	if (pos == -1) return 0; // is sorted
    	ans = min(ans, pos + 1); // delete the first element 0 ~ pos
    	ans = min(ans, n - 1 - f[0]); // delete the last element 
    	// delete the internal elements
    	vector<int> a;
    	for (int i = pos + 1; i < n; ++i) a.emplace_back(arr[i]);
    	for (int i = 1; i <= f[0] + 1; ++i) {
    		int v = arr[i - 1];
    		auto it = lower_bound(a.begin(), a.end(), v);
    		if (it == a.end()) break;
    		int p = it - a.begin();
    		// p means the pos + 1 + p in arr
    		// delete i.... pos + p
    		ans = min(ans, pos + p - i + 1);
    	}
    	return ans;
    }
};