// https://leetcode.cn/problems/smallest-rotation-with-highest-score/
// 考虑什么时候元素可以得分，逆向思维
// 差分数组统计区间的重复度


class Solution {
public:
    int bestRotation(vector<int>& nums) {
    	int n = nums.size();
    	// 数组整体向左移动了k次相当于k论调

    	vector<int> a(n + 1, 0);

    	for (int i = 0; i < n; ++i) {
    		int l = (i + 1) % n;
    		int r = (i - nums[i] + n) % n;
    		if (r >= l) {
    			// 对于k处于[l,r]都是合法的
    			++a[l];
    			--a[r + 1];
    		}
    		else {
    			// l>r，说明是第二种情况，对应了两个区间
    			// [0,r] + [l,n-1]
    			++a[0];
    			++a[l];
    			--a[r + 1];
    			--a[n];
    		}
    	}
    	int cur = 0;
    	int ans = 0, res = -1;
    	for (int i = 0; i <= n; ++i) {
    		cur += a[i];
    		if (cur > ans) {
    			res = i;
    			ans = cur;
    		}
    	}
    	return res;
    }
};