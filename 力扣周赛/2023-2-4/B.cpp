class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        unordered_map<int, bool> hs;
        for (auto c : banned) hs[c] = true;


        int cur = 0, cnt = 0;
        for (int i = 1; i <= n && cur < maxSum; ++i) {
            if (hs[i]) continue;
            cur += i;
            ++cnt;
        }
        if (cur == maxSum) return cnt;
        if (cur > maxSum) --cnt;
        return cnt < 0 ? 0 : cnt;
    }
};