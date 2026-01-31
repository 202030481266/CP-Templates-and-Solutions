#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int val = *max_element(nums.begin(), nums.end()) - *min_element(nums.begin(), nums.end());
        return 1ll * val * k;
    }
};