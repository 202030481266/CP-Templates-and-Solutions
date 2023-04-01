class Solution {
public:
    int maximumCostSubstring(string s, string chars, vector<int>& vals) {
        vector<int> a(30);

        // a is 1, z is 26
        for (int i = 1; i <= 26; ++i) a[i] = i;
        for (int i = 0; i < chars.size(); ++i) {
            a[chars[i] - 'a' + 1] = vals[i];
        }
        int n = s.size();
        vector<int> sum(n + 1);
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[s[i - 1] - 'a' + 1];
        int mn = 0, ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = max(ans, sum[i] - mn);
            mn = min(mn, sum[i]);
        }
        return ans;
    }
};