typedef long long ll;
class Solution {
    ll x, t;
public:
    unordered_map<ll, int> cache;
    unordered_map<ll, int> vis;  // 防止死循环
    int dfs(ll val) {
        if (cache.count(val)) return cache[val];
        if (x > val) return min(2 * val - 1, 2 * (x - val));
        int p = 1;
        ll tmp = x;
        while (tmp <= val) tmp *= x, ++p;
        if (tmp / x == val) return p - 2;
        vis[val] = 1;
        int res = p - 1 + dfs(val - tmp / x); // 加法逼近
        if (vis[tmp - val] != 1) 
            res = min(res, p + dfs(tmp - val));  // 减法逼近
        vis[val] = 0;
        return cache[val] = res;
    }
    int leastOpsExpressTarget(int X, int T) {
        x = X, t = T;
        cache[1] = 1;
        return dfs(t);
    }
};