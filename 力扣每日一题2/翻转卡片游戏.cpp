class Solution {
    int a[2001], b[2001];
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        int n = fronts.size();
        for (int i = 0; i < n; ++i) {
            if (fronts[i] == backs[i]) a[fronts[i]] = 1;
            b[fronts[i]] = b[backs[i]] = 1;
        }
        for (int i = 1; i <= 2000; ++i) {
            if (!b[i]) continue;
            if (!a[i]) return i;
        }
        return 0;
    }
};