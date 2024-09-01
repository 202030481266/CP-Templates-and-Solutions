#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int cnt[10];

class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums) {
        int n = nums.size();
        // C(n,2) - sum(C(x,2))
        ll ans = 0;
        while (nums[0]) {
            for (int i = 0; i< n; ++i) {
                cnt[nums[i] % 10]++;
                nums[i] /= 10;
            }
            ll res = 0;
            for (int i = 0; i < 10; ++i) {
                if (cnt[i]) {
                    res += 1ll* cnt[i] * (cnt[i] - 1) / 2;
                }
            }
            ans += 1ll*n*(n-1)/2 - res;
        }
        return ans;
    }
};