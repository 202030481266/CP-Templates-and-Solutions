class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        unordered_map<char,int> s;
        int n = words.size();
        vector<int> a(n);

        int i = 0;
        for (auto p : words) {
            int sc = 0;
            for (auto ch : p) sc += score[ch - 'a'];
            a[i++] = sc;
        }

        for (auto c : letters)
            ++s[c];

        auto f = [&](string u, unordered_map<char,int> status) -> bool {
            auto ss = status;
            for (auto c : u) {
                if (ss[c] == 0) return false;
                --ss[c];
            }
            return true;
        };
        int ans = 0;
        function<void(int,int,unordered_map<char,int>)> dfs = [&](int p,int val,unordered_map<char,int> status) {
            if (p == n) {
                ans = max(ans, val);
                return;
            }
            // 尝试寻找下面的
            if (f(words[p], status)) {
                auto ss = status;
                for (auto c : words[p]) --ss[c];
                dfs(p + 1, val + a[p], ss);
            }
            dfs(p + 1, val, status);
        };
        dfs(0, 0, s);
        return ans;
    }
};