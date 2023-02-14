class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();

        for (int i = 0; i < n; ++i)
            hours[i] = (hours[i] > 8) ? 1 : -1;

        vector<int> sum(n + 1);
        unordered_map<int,int> a;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + hours[i];
            if (!a.count(sum[i])) a[sum[i]] = i;
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (sum[i]) ans = max(ans, i);
            else {
                // try to find s[i] - 1
                if (a.count(sum[i] - 1)) 
                    ans = max(ans, i - a[sum[i] - 1]);
            }
        }
        return ans;
    }
};