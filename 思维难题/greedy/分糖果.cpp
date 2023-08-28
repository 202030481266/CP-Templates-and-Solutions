class Solution {
public:
    int candy(vector<int>& b) {
        int n = b.size();
        vector<int> a(n);
        a[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (b[i] > b[i - 1]) a[i] = a[i - 1] + 1;
            else a[i] = 1;
        }
        for (int i = n - 2; i >= 0; --i) {
            if (b[i] > b[i + 1] && a[i] <= a[i + 1])
                a[i] = a[i + 1] + 1;
        }
        return accumulate(a.begin(), a.end(), 0);
    }
};