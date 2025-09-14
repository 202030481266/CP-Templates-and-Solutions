#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

bitset<4001> bs;

class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        int n = nums.size();
        bs.reset();
        bs.set(0);
        ranges::sort(nums);
        vector<bool> ans(n);
        int l = 0, p = 0;
        for (int i = 1; i <= n; ++i) {
            while (l < n && nums[l] <= i) ++l;
            while (p < l) {
                bs |= (bs << nums[p]);
                p++;
            }
            // [l, n) could be i
            if (bs.test(k)) {
                for (int j = i; j <= n; ++j) {
                    ans[j - 1] = true;
                    break;
                }
            }
            else {
                for (int j = 1; j <= n - l && j * i <= k; j++) {
                    if (bs.test(k - j * i)) {
                        ans[i - 1] = true;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};