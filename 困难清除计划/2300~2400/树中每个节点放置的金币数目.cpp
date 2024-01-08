// xiaoshulin
// 2024.1.8

const int inf = 0x3f3f3f3f;
class Node {
private:
    int min1, min2, min3; // 存储最小的三个数字
    int max1, max2, max3; // 存储最大的三个数字
						  
public:
    Node() {
        min1 = min2 = min3 = INT_MAX; // 初始化为最大值
        max1 = max2 = max3 = INT_MIN; // 初始化为最小值
    }

	void updateMax(int number) {
		// 更新最大的三个 >= 0
        if (number > max1) {
            max3 = max2;
            max2 = max1;
            max1 = number;
        } else if (number > max2) {
            max3 = max2;
            max2 = number;
        } else if (number > max3) {
            max3 = number;
        }
	}

    void updateMin(int number) {
        // 更新最小的三个 < 0
        if (number < min1) {
            min3 = min2;
            min2 = min1;
            min1 = number;
        } else if (number < min2) {
            min3 = min2;
            min2 = number;
        } else if (number < min3) {
            min3 = number;
        }
    }

	void add(int number) {
		if (number >= 0)
			updateMax(number);
		else
			updateMin(number);
	}

	void update(Node& rhs) {
		// update max values
		updateMax(rhs.max1);
		updateMax(rhs.max2);
		updateMax(rhs.max3);

		// update min values
		updateMin(rhs.min1);
		updateMin(rhs.min2);
		updateMin(rhs.min3);
	}

	int get_max_number() {
		int sz = 0;
		if (max1 > INT_MIN) ++sz;
		if (max2 > INT_MIN) ++sz;
		if (max3 > INT_MIN) ++sz;
		return sz;
	}

	int get_min_number() {
		int sz = 0;
		if (min1 < INT_MAX) ++sz;
		if (min2 < INT_MAX) ++sz;
		if (min3 < INT_MAX) ++sz;
		return sz;
	}

	long long get_max_multi() {
		long long ans = -1e13;
		// if the result is >= 0
		int mx = get_max_number(), mn = get_min_number();
		if (mx == 3) {
			ans = max(ans, 1ll * max1 * max2 * max3);
		}
		if (mx >= 1 && mn >= 2) {
			ans = max(ans, 1ll * max1 * min1 * min2);
		}
		if (ans >= 0) return ans;
		// if the result is < 0
		if (mn == 3) {
			ans = max(ans, 1ll * min1 * min2 * min3);
		}
		if (mn >= 1 && mx >= 2) {
			int _min = min1;
			if (mn == 2) _min = min2;
			else if (mn == 3) _min = min3;
			if (mx == 2) {
				ans = max(ans, 1ll * _min * max1 * max2);
			}
			else {
				ans = max(ans, 1ll * _min * max2 * max3);
			}
		}
		return ans;
	}
};
class Solution {
	using ll = long long;
public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
		int n = cost.size();

		vector<int> g[n]; 
		for (auto& e : edges) {
			g[e[0]].push_back(e[1]);
			g[e[1]].push_back(e[0]);
		}

		vector<int> siz(n);
		vector<ll> ans(n);

		function<Node(int, int)> dfs = [&](int u, int fa) -> Node {
			Node cur;
			cur.add(cost[u]);
			siz[u] = 1;
			for (int& v : g[u]) { 
				if (v == fa) continue;
				Node tmp = dfs(v, u);
				cur.update(tmp);
				siz[u] += siz[v];
			}
			if (siz[u] < 3) {
				ans[u] = 1;
			}
			else {	
                ans[u] = max(0ll, cur.get_max_multi());
			}
			return cur;
		};

		dfs(0, 0);

		return ans;
    }
};

