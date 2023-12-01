class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        //  <= is 0, >= 1
        int n = trips.size();
        int dir = trips[0][1] - trips[0][2];
        for (int i = 1; i < n; ++i) 
            if ((trips[i][1] - trips[i][2]) * dir < 0) return false;
        vector<int> cnt(1010);
        for (auto& p : trips) {
            int x = min(p[2], p[1]), y = max(p[2], p[1]);
            ++x, ++y;
            // [x,y)
            cnt[x] += p[0];
            cnt[y] -= p[0];
        }
        int tmp = 0;
        for (int i = 1; i <= 1001; ++i) {
            tmp += cnt[i];
            if (tmp > capacity) return false;
        }
        return true;
    }
};