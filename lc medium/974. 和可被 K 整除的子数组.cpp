#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum(n);
        partial_sum(nums.begin(), nums.end(), sum.begin());
        for (int& v : sum) v = (v % k + k) % k;
        vector<int> cnt(k, 0);
        cnt[0] = 1;
        int ans = 0;
        for (int v : sum) {
            ans += cnt[v];
            cnt[v]++;
        }
        return ans;
    }
};