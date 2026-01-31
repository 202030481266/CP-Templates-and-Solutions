#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 容斥原理 + 动态规划

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());
        
        vector<ll> dp(mx+1), cnt(mx+1);
        vector<ll> num(mx+1); 

        for (int v : nums) cnt[v] += 1;
        for (int i = 1; i <= mx; ++i) {
            for (int j = i; j <= mx; j += i) {
                num[i] += cnt[j]; // k * i, number
            }
        }

        for (int i = mx; i >= 1; --i) {
            dp[i] = num[i] * (num[i]-1) / 2;
            for (int j = i * 2; j <= mx; j += i) {
                dp[i] -= dp[j];
            }
        }

        vector<ll> sum(mx+1);
        for (int i = 1; i <= mx; ++i) sum[i] = sum[i-1] + dp[i];

        vector<int> ans;
        for (ll q : queries) {
            // find the minimum element that sum[k] >= q
            q++;
            int l = 0, r = mx + 1;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (sum[mid] >= q) r = mid; // (l, mid) is not sure 
                else l = mid; // (mid, r) is not sure
            }
            ans.push_back(r);
        }
        return ans;
    }
};