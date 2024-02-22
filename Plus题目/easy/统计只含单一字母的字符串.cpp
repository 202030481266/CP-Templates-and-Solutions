class Solution {
public:
    int countLetters(string s) {
        int n = s.size(), ans = 0;
        int l = -1;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            l = -1;
            for (int i = 0; i < n; ++i) {
                if (s[i] == ch) {
                    if (l == -1) l = i;
                }
                else {
                    // [l, i)
                    if (l != -1) {
                        int len = i - l;
                        // 1 + 2 + 3 + ... len
                        ans += (len + 1) * len / 2;
                        l = -1;
                    }
                }
            }
            if (l != -1) ans += (n - l + 1) * (n - l) / 2;
        }
        return ans;
    }
};