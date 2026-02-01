#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int lengthOfLIS(std::vector<int>& nums) {
    if (nums.empty()) return 0;

    std::vector<int> tails;
    
    for (int num : nums) {
        if (tails.empty() || num > tails.back()) {
            tails.push_back(num);
        } 
        else {
            auto it = std::lower_bound(tails.begin(), tails.end(), num);
            *it = num;
        }
    }
    
    return tails.size();
}
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int mx = *ranges::max_element(nums);
        int b = bit_width(1u * mx);
        int ans = 0;
        for (int i = 0; i < b; ++i) {
            vi arr;
            for (int v : nums) {
                if (v >> i & 1) arr.push_back(i);
            }
            ans = max(ans, lengthOfLIS(arr));
        }
        return ans;
    }
};