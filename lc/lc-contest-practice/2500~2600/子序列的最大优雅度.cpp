class Solution {
public:
    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        long long ans = 0;
        sort(items.begin(), items.end());
        int n = items.size(), a[n + 1], b[n + 1];
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        vector<int> rem;
        int type = 0;
        for (int i = n - k; i < n; ++i) {
            ans += items[i][0];
            if (a[items[i][1]] > 0) {
                rem.push_back(min(a[items[i][1]], items[i][0]));
                a[items[i][1]] = max(a[items[i][1]], items[i][0]);
                b[items[i][1]] = 1;
            }
            else a[items[i][1]] = items[i][0], ++type;
        }     
        vector<int> use;
        for (int i = 0; i < n - k; ++i) {
            if (a[items[i][1]] == 0) {
                b[items[i][1]] = max(b[items[i][1]], items[i][0]);
            }
        }
        for (int i = 0; i < n - k; ++i) {
            if (a[items[i][1]] == 0) {
                use.push_back(b[items[i][1]]);
                a[items[i][1]] = 1;
            }
        }
        int m = min((int)use.size(), (int)rem.size());
        sort(use.begin(), use.end(), greater<int>());
        sort(rem.begin(), rem.end());
        long long sub = 0, res = ans;
        ans += 1ll * type * type;
        for (int i = 0; i < m; ++i) {
            // cout << ans << endl;
            sub += (rem[i] - use[i]);
            ans = max(ans, res - sub + (type + i + 1) * (type + i + 1));
        }
        return ans;
    }
};




