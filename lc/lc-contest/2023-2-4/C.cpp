class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        unordered_map<int,int> hs;
        for (auto c : prizePositions) ++hs[c];

        prizePositions.erase(unique(prizePositions.begin(), prizePositions.end()), prizePositions.end());
        int n = prizePositions.size();
        vector<int> sum(n + 1);
        vector<int> a(n + 1), b(n + 1);
        // every number is different
        for (int i = 1; i <= n; ++i) 
            sum[i] = sum[i - 1] + hs[prizePositions[i - 1]];
        // to right
        for (int i = 1; i <= n; ++i) {
            int temp = prizePositions[i - 1] + k;
            auto right = lower_bound(prizePositions.begin(), prizePositions.end(), temp);
            if (right == prizePositions.end()) {
                a[i] = sum[n] - sum[i - 1];
                b[i] = n;
            } else {
                int pos = right - prizePositions.begin();
                if (prizePositions[pos] > temp) {
                    a[i] = sum[pos] - sum[i - 1];
                    b[i] = pos;
                } else {
                    a[i] = sum[pos + 1] - sum[i - 1];
                    b[i] = pos + 1;
                }
            }
        }
        vector<int> maxx(n + 2);
        for (int i = n; i >= 1; --i)
            maxx[i] = max(maxx[i + 1], a[i]);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = max(ans, maxx[b[i] + 1] + a[i]);
        }
        return ans;
    }
};