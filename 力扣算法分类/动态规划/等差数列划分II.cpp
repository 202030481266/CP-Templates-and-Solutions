// https://leetcode.cn/problems/arithmetic-slices-ii-subsequence/
// 卡常卡的很猛（第一个版本是1000ms左右，第二个版本是500ms）根本没有意义


// class Solution {
// public:
//     int numberOfArithmeticSlices(vector<int>& nums) {
//     	int n = nums.size();
//     	unordered_map<long long, int> f[n];
//      unordered_map<long long, int> g[n];

//         // 卡超时了
//     	for (int i = 1; i < n; ++i) {
//     		for (int j = 0; j < i; ++j) {
//     			long long t = 1ll * nums[i] - nums[j];
//     			f[i][t] += f[j][t];
//     			f[i][t] += g[j][t];
//     			g[i][t] += 1;
//     		}
//     	}
//     	int ans = 0;
//     	for (int i = 2; i < n; ++i) {
//     		for (auto [x, y] : f[i]) {
//     			ans += y;
//     		}
//     	}
//     	return ans;
//     }
// };


class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
    	int n = nums.size();
    	unordered_map<long long, int> f[n];

    	int ans = 0;
    	// g 只能影响后来的，因此一边统计一边更新
    	for (int i = 1; i < n; ++i) {
    		for (int j = 0; j < i; ++j) {
    			long long t = 1ll * nums[i] - nums[j];
    			f[i][t] += f[j][t];
    			ans += f[j][t];
    			f[i][t] += 1;
    		}
    	}
    	return ans;
    }
};

