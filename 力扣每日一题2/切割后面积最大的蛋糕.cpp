class Solution {
    typedef unsigned long long ull;
    static constexpr int mod = 1e9 + 7;
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        ull x = 0, y = 0;
        horizontalCuts.push_back(0);
        horizontalCuts.push_back(h);
        verticalCuts.push_back(0);
        verticalCuts.push_back(w);
        int n = horizontalCuts.size(), m = verticalCuts.size();
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        for (int i = 1; i < n; ++i) 
            x = max(x, 1ull * horizontalCuts[i] - horizontalCuts[i - 1]);
        for (int i = 1; i < m; ++i)
            y = max(y, 1ull * verticalCuts[i] - verticalCuts[i - 1]);
        return x * y % mod;
    }
};