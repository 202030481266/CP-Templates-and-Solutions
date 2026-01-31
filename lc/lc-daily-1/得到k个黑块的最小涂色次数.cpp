class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.size();
        vector<int> a(n + 1);

        for (int i = 1; i <= n; ++i) 
            a[i] = a[i - 1] + (blocks[i - 1] == 'W');
        int ans = INT_MAX;
        for (int i = k; i <= n; ++i)
            ans = min(ans, a[i] - a[i - k]);
        return ans;
    }
};