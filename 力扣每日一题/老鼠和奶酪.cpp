class Solution {
    typedef pair<int, int> pii;
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();
        if (n == k) 
            return accumulate(reward1.begin(), reward1.end(), 0);
        vector<pii> a;
        for (int i = 0; i < n; ++i) 
            a.emplace_back(reward1[i] - reward2[i], i);
        int ans = 0;
        sort(a.begin(), a.end());
        for (int i = n - 1; i >= n - k; --i) ans += reward1[a[i].second];
        for (int i = 0; i < n - k; ++i) ans += reward2[a[i].second];
        return ans;
    }
};