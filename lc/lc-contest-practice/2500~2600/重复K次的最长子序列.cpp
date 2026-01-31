class Solution {
    int cnt[26], n, K;
    string ans, t;
public:
    void dfs(string s) {
        cout << s << '\n';
        if (s.size() > ans.size()) ans = s;
        else if (s.size() == ans.size() && s > ans) ans = s;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (cnt[ch - 'a'] < K) continue;
            string ss = s;
            ss.push_back(ch);
            int p = 0, c = 0, m = ss.size();
            for (int i = 0; i < n; ++i) {
                if (t[i] == ss[p]) {
                    p = (p + 1) % m;
                    if (p == 0) {
                        ++c;
                        if (c == K) {
                            dfs(ss);
                            break;
                        }
                    }
                }
            }
        }
    }
    void test(string s) {
        int p = 0, c = 0, m = s.size();
        for (int i = 0; i < n; ++i) {
            if (t[i] == s[p]) {
                p = (p + 1) % m;
                if (p == 0) {
                    ++c;
                }
            }
        }
        cout << s << ' ' << c << endl;
    }
    string longestSubsequenceRepeatedK(string s, int k) {
        t = s;
        n = s.size();
        K = k;
        for (char& c : s) ++cnt[c - 'a'];
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] >= k) {
                string tmp;
                tmp.push_back((char)(i + 'a'));
                dfs(tmp);
            }
        }
        // cout << "test\n";
        // test("let");
        return ans;
    }
};
