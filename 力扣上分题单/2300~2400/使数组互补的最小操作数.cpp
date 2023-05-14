// https://leetcode.cn/problems/minimum-moves-to-make-array-complementary/



class Solution {
	int f[200010];
public:
    int minMoves(vector<int>& nums, int limit) {
    	// 将这两个数字的和设置为区间[2,2*limit]中的某一个数就一定有解
    	int n = nums.size();
    	memset(f, 0, sizeof(f));
    	for (int i = 0; i < n / 2; ++i) {
    		int x = nums[i], y = nums[n - 1 - i];
    		int l = min(x + 1, y + 1), r = max(x + limit, y + limit);
    		++f[l]; --f[x + y];  //[l,(x+y)-1]
    		++f[x + y + 1]; --f[r + 1]; // [(x+y)+1,r]
    		if (l - 1 >= 2) {
    			f[2] += 2; 
    			f[l] -= 2; //[2,l-1]
    		}
    		if (r + 1 <= 2 * limit) {
    			f[r + 1] += 2; 
    			f[2 * limit + 1] -= 2; // [r+1,2*limit]
    		}
    	}
    	int res = 0, ans = INT_MAX;
    	for (int i = 2; i <= 2 * limit; ++i) {
    		res += f[i];
    		if (res < ans) ans = res;
    	}
    	return ans;
    }
};