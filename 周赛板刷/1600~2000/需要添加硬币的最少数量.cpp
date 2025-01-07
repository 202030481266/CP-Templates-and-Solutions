// 贪心构造
class Solution {
public:
    int minimumAddedCoins(vector<int>& coins, int target) {
        int n = coins.size();
        // greedy construct, as we can see the smaller number is more difficult to construct
        vector<int> cnt(target + 1);

        for (int& v : coins)
            if (v <= target) ++cnt[v];

        long long right = 0; 
        int ans = 0;

        for (int i = 1; i <= target && right < target; ++i) {
            if (right < i && cnt[i] == 0) {
                ++ans;
                // [1, right] -> [1, i + right]
                // actually right should be i - 1
                assert(right == i - 1);
                right = i * 2 - 1;
            }
            else {
                // [1, right] -> [1, right + cnt[i] * i]
                if (cnt[i]) right += cnt[i] * i;
            }
        }
        return ans;
    }
};