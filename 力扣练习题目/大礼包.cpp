// https://leetcode.cn/problems/shopping-offers/



// 二进制状态规划会超时，莫名其妙
class Solution {
public:
    int dp[1 << 24];
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
    	int n = price.size();
        memset(dp, -1, sizeof(dp));
    	vector<vector<int>> a;

    	for (auto c :special) {
    		bool flag = true;
    		for (int i = 0; i < n; ++i)
    			if (c[i] > needs[i]) flag = false;
    		if (flag) a.emplace_back(c);
        }
    	for (int i = 0; i < n; ++i) {
    		vector<int> temp(n + 1, 0);
    		temp[n] = price[i];
    		temp[i] = 1;
    		a.emplace_back(temp);
    	}
    	function<int(int)> dfs = [&](int S) -> int {
    		if (S == 0) return 0;
    		if (dp[S] != -1) return dp[S];
    		vector<int> cur(n);
    		for (int i = 0; i < n; ++i) {
    			cur[i] = ((S >> (4 * i)) & 15);
    		}
    		int use = INT_MAX;
    		for (int i = 0; i < a.size(); ++i) {
    			bool flag = true;
    			for (int j = 0; j < n; ++j)
    				if (cur[j] < a[i][j]) flag = false;
    			if (flag) {
    				int t = 0;
    				for (int j = 0; j < n; ++j)
    					t = (t | ((cur[j] - a[i][j]) << (j * 4)));
    				int k = dfs(t);
    				if (k != INT_MAX)
    					use = min(use, k + a[i][n]);
    			}
    		}
    		return dp[S] = use;
    	};
    	int S = 0;
    	for (int i = 0; i < n; ++i)
    		S = (S | (needs[i] << (i * 4)));
    	return dfs(S);
    }
};


// 使用哈希表的背包就不会超时
class Solution {
public:
    map<vector<int>, int> memo;

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int n = price.size();

        // 过滤不需要计算的大礼包，只保留需要计算的大礼包
        vector<vector<int>> filterSpecial;
        for (auto & sp : special) {
            int totalCount = 0, totalPrice = 0;
            for (int i = 0; i < n; ++i) {
                totalCount += sp[i];
                totalPrice += sp[i] * price[i];
            }
            if (totalCount > 0 && totalPrice > sp[n]) {
                filterSpecial.emplace_back(sp);
            }
        }

        return dfs(price, special, needs, filterSpecial, n);
    }

    // 记忆化搜索计算满足购物清单所需花费的最低价格
    int dfs(vector<int> price,const vector<vector<int>> & special, vector<int> curNeeds, vector<vector<int>> & filterSpecial, int n) {
        if (!memo.count(curNeeds)) {
            int minPrice = 0;
            for (int i = 0; i < n; ++i) {
                minPrice += curNeeds[i] * price[i]; // 不购买任何大礼包，原价购买购物清单中的所有物品
            }
            for (auto & curSpecial : filterSpecial) {
                int specialPrice = curSpecial[n];
                vector<int> nxtNeeds;
                for (int i = 0; i < n; ++i) {
                    if (curSpecial[i] > curNeeds[i]) { // 不能购买超出购物清单指定数量的物品
                        break;
                    }
                    nxtNeeds.emplace_back(curNeeds[i] - curSpecial[i]);
                }
                if (nxtNeeds.size() == n) { // 大礼包可以购买
                    minPrice = min(minPrice, dfs(price, special, nxtNeeds, filterSpecial, n) + specialPrice);
                }
            }
            memo[curNeeds] = minPrice;
        }
        return memo[curNeeds];
    }
};

