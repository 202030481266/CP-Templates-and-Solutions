class Solution {
    typedef pair<int, int> pii;
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = values.size();
        vector<pii> a;
        for (int i = 0; i < n; ++i) a.emplace_back(values[i], labels[i]);
        sort(a.begin(), a.end());
        unordered_map<int, int> cnt;
        int ans = 0, use = 0;
        for (int i = n - 1; i >= 0 && use <= numWanted; --i) {
            if (cnt[a[i].second] <= useLimit) {
                ++cnt[a[i].second];
                ++use;
                ans += a[i].first;
            }
        }
        return ans;
    }
};