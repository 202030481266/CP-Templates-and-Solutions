// 动态规划反而超时了，真无语啊
// 这道题目卡常了
class Solution {
    unordered_map<int, unordered_set<int>> mp;
public:
    unordered_set<int> dfs(string& s, int p, int n) {
        if (p == s.size()) return {0};
        if (mp.count(p)) return mp[p];
        auto& res = mp[p];
        int x = 0;
        for (int i = p; i < s.size(); ++i) {
            // [p, i] is a segment
            x = x * 10 + s[i] - '0';
            if (x > n) break;
            auto tmp = dfs(s, i + 1, n);
            for (int v : tmp) 
                if (v + x <= n)
                    res.insert(v + x);
        }
        return res;
    }
    int punishmentNumber(int n) {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            mp.clear();
            string ii = to_string(i * i);
            auto res = dfs(ii, 0, i);
            if (res.count(i)) ans += i * i;
        }
        return ans;
    }
};


// 爆搜反而轻而易举地过掉了这道题目，按道理不应该把！
class Solution {
public:
    bool dfs(string &s, int pos, int tot, int target) {
        if (pos == s.size()) {
            return tot == target;
        } 
        int sum = 0;
        for (int i = pos; i < s.size(); i++) {
            sum = sum * 10 + s[i] - '0';
            if (sum + tot > target) {
                break;
            }
            if (dfs(s, i + 1, sum + tot, target)) {
                return true;
            }
        }
        return false;
    }
    
    int punishmentNumber(int n) {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            string s = to_string(i * i);
            if (dfs(s, 0, 0, i)) {
                res += i * i;
            }
        }
        return res;
    }
};
