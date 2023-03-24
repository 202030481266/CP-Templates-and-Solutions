// https://leetcode.cn/problems/total-appeal-of-a-string/



class Solution {
public:
    long long appealSum(string s) {
        int n = s.size();

        auto cal = [](long long len) -> long long {
            return 1ll * len * (len + 1) / 2ll;
        };

        long long ans = cal(n) * 26;

        vector<vector<int>> pos(26);
        for (int i = 0; i < n; ++i) {
            pos[s[i] - 'a'].emplace_back(i);
        }
        for (int i = 0; i < 26; ++i) {
            if (pos[i].size() > 0) {
                int l = 0, r = 0, p = 0, m = pos[i].size();
                while (p <= m) {
                    l = (p == 0 ? 0 : pos[i][p - 1] + 1);
                    r = (p == m ? n - 1: pos[i][p] - 1);
                    if (r >= l) {
                        // the substring don't have the i character
                        ans -= cal(r - l + 1);
                    }
                    ++p;
                }
            }
            else {
                ans -= cal(n);
            }
        }
        return ans;
    }
};