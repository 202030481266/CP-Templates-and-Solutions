#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int base[32];

class Solution {
public:
    int maxXorSubsequences(vector<int>& nums) {
        int n = nums.size();
        memset(base, 0, sizeof(base));
        int ans = 0;
        for (int v : nums) {
            for (int i = 31; i >= 0; --i) {
                if ((v >> i) & 1) {
                    if (base[i]) v ^= base[i];
                    else {
                        base[i] = v;
                        break;
                    }
                }
            }
        }
        for (int i = 31; i >= 0; --i) ans = max(ans, ans ^ base[i]);
        return ans;
    }
};