#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

int cnt[100005];

class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        int n = nums.size(), mx = 0;
        for (int v : nums) {
            ++cnt[v];
            mx = max(mx, cnt[v]);
        }
        for (int v : nums) cnt[v] = 0;
        return (n % k == 0 && n / k >= mx);
    }
};