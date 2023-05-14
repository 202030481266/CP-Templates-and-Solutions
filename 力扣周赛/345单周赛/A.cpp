class Solution {
public:
    vector<int> circularGameLosers(int n, int k) {
        vector<int> cnt(n);
        int cur = 0, loop = 1;
        while (true) {
            ++cnt[cur];
            if (cnt[cur] == 2) break;
            cur = (cur + loop * k) % n;
            ++loop;
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) 
            if (cnt[i] == 0) ans.emplace_back(i + 1);
        return ans;
    }
};