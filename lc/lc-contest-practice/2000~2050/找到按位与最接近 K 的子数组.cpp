#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

const int ini = ~0u>>1;

class Solution {
public:
    int minimumDifference(vector<int>& nums, int K) {
        // 模板题
        int n = nums.size(), ans = 0x3f3f3f3f;
        vector<pii> a;
        for (int i = 0; i < n; ++i) {
            a.emplace_back(ini, i);
            int k = 0;
            a[0].first &= nums[i];
            for (int j = 1; j < a.size(); ++j) {
                a[j].first &= nums[i];
                if (a[j].first == a[k].first) a[k].second = a[j].second;
                else a[++k] = a[j];
            }
            a.resize(k+1);
            for (auto& v : a) ans = min(ans, abs(v.first-K));
        }
        return ans;
    }
};