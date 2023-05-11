class Solution {
public:
    bool queryString(string s, int val) {
        string x;
        int tmp = val;
        while (tmp) {
            x = to_string(tmp % 2) + x;
            tmp /= 2;
        }
        int m = x.size(), n = s.size();
        unordered_set<int> h;
        for (int len = 1; len <= min(m, n); ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                if (s[i] == '1') {
                    int j = i + len - 1, res = 0;
                    for (int k = i; k <= j; ++k) res = res * 2 + (s[k] - '0');
                    h.emplace(res);
                }
            }
        }
        for (int i = 1; i <= val; ++i)
            if (!h.count(i)) return false;
        return true;
    }
};