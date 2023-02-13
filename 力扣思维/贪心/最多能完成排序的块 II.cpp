// https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/
// 贪心匹配：一直往前，如果刚好使得排名前面几个数都在一起，那么就可以分为一块


class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
    	int n = arr.size();
    	vector<int> a(arr.begin(), arr.end());
    	unordered_map<int, vector<int>> pos;
    	unordered_map<int, int> nxt;

    	sort(a.begin(), a.end());
    	for (int i = 0; i < n; ++i) {
    		pos[a[i]].emplace_back(i);
    		if (!nxt.count(a[i])) nxt[a[i]] = 0;
    	}

    	int ans = 0;
    	int cur = INT_MIN;
    	for (int i = 0; i < n; ++i) {
    		int x = pos[arr[i]][nxt[arr[i]]++];
    		cur = max(cur, x);
    		if (i == cur) ++ans;
    	}
    	return ans;
    }
};