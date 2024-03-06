// 博弈论
// 超时的暴力搜索做法
class Solution {
public:
	using ll = long long;
    bool canWin(string currentState) {
    	int n = currentState.size();
    	ll s = 0;
    	for (int i = 0; i < n; ++i) {
    		if (currentState[i] == '+') s |= (1ll << i);
    	}

    	unordered_map<ll, int> sg;

    	function<int(int)> dfs = [&](ll status) -> int {
    		if (sg.count(status)) return sg[status];
            int res = 0;
    		for (int i = 0; i + 1 <= n; ++i) {
    			if (((status >> i) & 1) && ((status >> (i + 1)) & 1)) {
    				int tmp = dfs(status ^ (3ll << i));
                    if (tmp == 0) {
                        res = 1;
                        break;
                    }
    			}
    		}
            sg[status] = res;
    		return sg[status];
    	};

        return dfs(s);
    }
};


// 将状态划分为nim问题，划分为几堆石子，其中每一次只能从中取走2个石头
// 这个游戏是一个公平组合游戏，那么就可以使用SG定理
// 博弈论
class Solution {
public:
	vector<int> sg;
    int dfs(int n) {
        if (sg[n] != -1) return sg[n];
        set<int> s;
        for (int i = 0; i + 1 < n; ++i) {
            // [0, i), (i + 1, n)
            s.insert(dfs(i) ^ dfs(n - i - 2));
        }
        int i = 0;
        while (s.find(i) != s.end()) ++i;
        return sg[n] = i;
    }
    bool canWin(string currentState) {
    	int pre = -1, n = currentState.size(), ans = 0;
        sg = vector<int>(61, -1);
        sg[0] = sg[1] = 0;
        sg[2] = sg[3] = 1;
        for (int i = 0; i < n; ++i) {
            if (currentState[i] == '+') {
                if (pre == -1) pre = i;
            }
            else {
                if (pre != -1) {
                    // [pre, i)
                    ans ^= dfs(i - pre);
                    pre = -1;
                }
            }
        }
        if (pre != -1) ans ^= dfs(n - pre);
        return ans > 0;
    }
};
