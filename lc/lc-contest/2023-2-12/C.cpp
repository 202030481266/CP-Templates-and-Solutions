// 就是纯暴力，想太多了

class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();
        const int MAXP = 30;
        typedef pair<int, int> pii;
        unordered_map<int, pii> mp;
        // 记录所有长度小于等于 30 的子串的值和位置
        for (int p = 1; p <= MAXP && p <= n; p++) {
            int t = 0;
            // 长度为 p 的第一个子串
            for (int i = 0; i < p; i++) t |= (s[i] - '0') << (p - i - 1);
            if (!mp.count(t)) mp[t] = pii(0, p - 1);
            // 长度为 p 的后续子串
            for (int i = p; i < n; i++) {
                t &= (1 << (p - 1)) - 1;
                t <<= 1;
                t |= s[i] - '0';
                if (!mp.count(t)) mp[t] = pii(i - p + 1, i);
            }
        }

        // O(1) 回答询问
        vector<vector<int>> ans;
        for (auto &qry : queries) {
            int x = qry[0] ^ qry[1];
            if (mp.count(x)) ans.push_back({mp[x].first, mp[x].second});
            else ans.push_back({-1, -1});
        }
        return ans;
    }
};

