/*
	单调栈优化dp （单调栈+二分）
*/

// 模板题1：https://leetcode.cn/problems/minimum-number-of-visited-cells-in-a-grid/
// f[i][j] = 1 + min(min(f[i][k], k in [j + 1, j + g]), min(f[k][j], k in [i + 1, i + g])) 所以暴力的时间复杂度是o(mn(m+n))
// dp转移方程是一个单点更新和区间最小值查询的操作，所以可以从中得知使用线段树优化和单调栈优化。 将时间复杂度化简为o(mn(log m + log n))
class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
    	int n = grid.size(), m = grid[0].size(), mn;
    	vector<vector<pair<int, int>>> col_st(m);

    	// 逆序遍历
    	for (int i = n - 1; i >= 0; --i) {
    		vector<pair<int, int>> row_st;  // 当前的单调栈，按照从左往右的顺序看，下标变小，值变大
    		for (int j = m - 1; j >= 0; --j) {
    			mn = INT_MAX;  // f[i][j];
    			int g = grid[i][j];
    			auto &col = col_st[j];
    			if (i == n - 1 && j == m - 1) mn = 0; // dp[n - 1][m - 1] = 0;
    			else if (g) {
    				// 往右边寻找最大的不大于j+g的值
    				auto it = lower_bound(row_st.begin(), row_st.end(), j + g, [](const auto &a, const int b) {
    					return a.second > b;
    				});
    				if (it < row_st.end()) mn = min(mn, it->first);
    				// 往下找z最大的不大于i+g的值
    				it = lower_bound(col.begin(), col.end(), i + g, [](const auto &a, const int b) {
    					return a.second > b;
    				});
    				if (it < col.end()) mn = min(mn, it->first);
    			}
    			if (mn == INT_MAX) continue;  // 无解，无法到达
    			// 把这个格子加入到单调栈里面
    			++mn;  // f[i][j]
    			while (!row_st.empty() && row_st.back().first >= mn) row_st.pop_back();
    			row_st.emplace_back(mn, j);
    			while (!col.empty() && col.back().first >= mn) col.pop_back();
    			col.emplace_back(mn, i);
    		}
    	}
    	return mn == INT_MAX ? -1 : mn;
    }
};


/*
    bitset优化01背包（主要是和布尔运算相关，可以通过位运算位移统一计算）
    经过测试，数据规模在100000依然可以稳过
    https://leetcode.cn/problems/maximum-total-reward-using-operations-ii/description/
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int maxTotalReward(vector<int>& a) {
        // 观察1：贪心证明：最大的数字必选，假设这个数字就是mx
        // 观察2：一个子问题，如何能够构造出具体的一个数值似乎是更为基本的问题，显然不能贪心解决，考虑动态规划
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(),a.end()),a.end());
        int ans = a.back();
        a.pop_back();
        bitset<50000> dp;
        dp.set(0);
        for (int& v : a) {
            int m = 50000-v;
            dp |= ((dp<<m)>>m)<<v;
        }
        for (int i=ans-1; i >= 0; --i) {
            if (dp.test(i)) {
                ans += i;
                break;
            }
        }
        return ans;
    }
};