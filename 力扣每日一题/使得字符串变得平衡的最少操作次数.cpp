class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();

        vector<int> a(n + 1);
        vector<int> b(n + 1);

        for (int i = 1; i <= n; ++i) {
            a[i] = a[i - 1] + (s[i - 1] == 'a');
            b[i] = b[i - 1] + (s[i - 1] == 'b');
        }
        int ans = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            ans = min(ans, a[n] + b[i] - a[i]);
        }
        return ans;
    }
};