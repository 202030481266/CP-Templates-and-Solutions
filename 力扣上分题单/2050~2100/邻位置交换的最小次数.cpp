// https://leetcode.cn/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/
// 找到第k个排列，然后贪心的统计结果，暴力+模拟可以解决力扣80%的题目！！


class Solution {
public:
    int getMinSwaps(string num, int k) {
    	int n = num.size();
    	vector<int> a(n), b(n);
    	for (int i = 0; i < num.size(); ++i) {
    		a[i] = num[i] - '0';
    		b[i] = num[i] - '0';
    	}
    	while (k--) {
    		next_permutation(a.begin(), a.end());
    	}
    	// greedy
    	int ans = 0;
    	for (int i = 0; i < n; ++i) {
    		if (b[i] != a[i]) {
    			int pos = i;
    			for (int j = i + 1; j < n; ++j) {
    				if (a[j] == b[i]) {
    					pos = j;
    					break;
    				}
    			}
    			for (int j = pos; j > i; --j) {
    				swap(a[j], a[j - 1]);
    			}
    			ans += (pos - i);
    		}
    	}
    	return ans;
    }
};