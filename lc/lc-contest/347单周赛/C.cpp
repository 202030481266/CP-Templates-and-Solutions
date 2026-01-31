class Solution {
    typedef long long ll;
public:
    long long minimumCost(string s) {
        int n = s.size(); 
        ll r[n + 2][2], l[n + 2][2];
        memset(r, 0, sizeof(r));
        memset(l, 0, sizeof(l));
        if (s[n - 1] == '1') {
            r[n - 1][1] = 0;
            r[n - 1][0] = 1;
        }
        else {
            r[n - 1][1] = 1;
            r[n - 1][0] = 0;
        }
        for (int i = n - 2; i >= 0; --i) {
            if (s[i] == '1') {
                r[i][1] = r[i + 1][1];
                r[i][0] = r[i + 1][1] + (n - i);
            }
            else {
                r[i][0] = r[i + 1][0];
                r[i][1] = r[i + 1][0] + (n - i);
            }
        }
        if (s[0] == '1') {
            l[0][1] = 0;
            l[0][0] = 1;
        }
        else {
            l[0][1] = 1;
            l[0][0] = 0;
        }
        for (int i = 1; i < n; ++i) {
            if (s[i] == '1') {
                l[i][1] = l[i - 1][1];
                l[i][0] = l[i - 1][1] + i + 1;
            }
            else {
                l[i][0] = l[i - 1][0];
                l[i][1] = l[i - 1][0] + i + 1;
            }
        }
        ll ans = 2e15;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, l[i][0] + r[i + 1][0]);
            ans = min(ans, l[i][1] + r[i + 1][1]);
            int right = (i + 1 > n - 1 ? INT_MAX : n - i - 1);
            ans = min(ans, l[i][1] + r[i + 1][0] + min(i + 1, right));
            ans = min(ans, l[i][0] + r[i + 1][0] + min(i + 1, right));
        }
        return ans;
    }
};