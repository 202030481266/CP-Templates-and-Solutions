class Solution {
    typedef pair<int, int> pii;
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        unordered_map<int, int> h;
        unordered_map<int, bool> use; 
        for (auto& c : points) {
            if (h.count(c[0])) h[c[0]] = max(h[c[0]], c[1]);
            else h[c[0]] = c[1];
        }
        vector<pii> arr;
        for (auto& c : points) {
            if (!use[c[0]]) {
                arr.emplace_back(c[0], h[c[0]]);  // [x, y]
                use[c[0]] = 1;
            }
        }
        sort(arr.begin(), arr.end());
        int l = 0, n = arr.size(), ans = INT_MIN;
        multiset<int> s;
        for (int i = 0; i < n; ++i) {
            while (arr[l].first < arr[i].first - k) {
                auto it = s.lower_bound(arr[l].second - arr[l].first);
                s.erase(it);
                ++l;
            }
            if (l < i) 
                ans = max(ans, arr[i].first + arr[i].second + *s.rbegin());
            s.emplace(arr[i].second - arr[i].first);
        }
        return ans;
    }
}; 