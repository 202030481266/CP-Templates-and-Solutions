#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n);
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            while (x) {
                sum[i] += x % 10;
                x /= 10;
            }
        }
        ranges::sort(ids, [&sum, &nums](int i, int j){
            return (sum[i] != sum[j] ? sum[i] < sum[j] : nums[i] < nums[j]);
        });
        vector<int> vis(n);
        int ans = 0;
        for (int i = 0, cur, cnt = 0; i < n; ++i) {
            if (vis[i] || ids[i] == i) continue;
            cur = i;
            cnt = 0;
            while (!vis[cur]) {
                vis[cur] = 1;
                ++cnt;
                cur = ids[cur];
            }
            ans += cnt - 1;
        }
        return ans;
    }
};