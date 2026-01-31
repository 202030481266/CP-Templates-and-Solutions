class Solution {
public:
    int findTheLongestBalancedSubstring(string s) {
        int n = s.size();
        int ans = 0;
        for (int len = 2; len <= n; len += 2) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1, mid = i + len / 2 - 1;
                bool flag = true;
                for (int k = i; k <= mid; ++k) {
                    if (s[k] == '1') {
                        flag = false;
                        break;
                    }
                }
                if (!flag) continue;
                for (int k = mid + 1; k <= j; ++k) {
                    if (s[k] == '0') {
                        flag = false;
                        break;
                    }
                }
                if (flag) ans = max(ans, len);
            }
        }
        return ans;
    }
};