class Solution {
public:
    int maximumLength(string s) {
        int n = s.size();

        vector<int> cnt(n + 1);

        int ans = -1;
        for (int c = 0; c < 26; ++c) {
            // i is the character
            fill(cnt.begin(), cnt.end(), 0);
            int pre = -1;
            for (int i = 0; i < n; ++i) {
                if (s[i] - 'a' == c) {
                    if (pre == -1) pre = i;
                }
                else {
                    // [pre, i)
                    if (pre != -1) {
                        int len = i - pre;
                        if (len >= 3) {
                            ans = max(ans, len - 2);
                        }
                        cnt[len] += 1;
                        if (len >= 2) cnt[len - 1] += 2;
                        pre = -1;
                    }
                }
            }
            if (pre != -1) {
                // [pre, n)
                int len = n - pre;
                if (len >= 3) {
                    ans = max(ans, len - 2);
                }
                cnt[len] += 1;
                if (len >= 2) cnt[len - 1] += 2;
            }
            for (int i = n; i >= 1; --i) {
                if (cnt[i] >= 3) {
                    ans = max(ans, i);
                    break;
                }
            }
        }
        return ans;
    }
};