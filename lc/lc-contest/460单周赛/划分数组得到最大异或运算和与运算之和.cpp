#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ull = unsigned long long;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

ull base[32];

class Solution {
public:
    long long maximizeXorAndXor(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), greater<int>());
        memset(base, 0, sizeof(base));
        for (ull v : nums) {
            for (int i = 30; i >= 0; --i) {
                if ((v >> i) & 1) {
                    if (base[i]) v ^= base[i];
                    else {
                        base[i] = v;
                        break;
                    }
                }
            }
        }
        ull ans = 0, mx_xor = 0;
        for (int i = 30; i >= 0; --i) mx_xor = max(mx_xor, mx_xor ^ base[i]);
        for (ull v : nums) ans ^= v;
        ans = (ans ^ mx_xor) + mx_xor;
        auto dfs = [&](auto&& self, int i, ull s1, ull s2, ull s3) {
            if (i == n) {
                ans = max(ans, s1 + ((s2 == (1u << 31) - 1) ? 0 : s2) + s3);
                return;
            }
            int b = bit_width((ull)nums[i]);
            ull mx = (1u << b) - 1;
            if (s1 + s3 + 2 * mx + (s2 & nums[i]) > ans) {
                self(self, i + 1, s1, s2 & nums[i], s3);
            }
            if (s1 + s3 + 2 * mx + s2 > ans) {
                self(self, i + 1, s1 ^ nums[i], s2, s3);
                self(self, i + 1, s1, s2, s3 ^ nums[i]);
            }
        };
        dfs(dfs, 0, 0, (1u << 31) - 1, 0);
        return ans;
    }
};