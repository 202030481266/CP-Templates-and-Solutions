#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    vector<int> getModifiedArray(int n, vector<vector<int>>& updates) {
        vector<int> sum(n+1);
        for (auto& u : updates) {
            sum[u[0]] += u[2];
            sum[u[1]+1] -= u[2];
        }
        vector<int> ans(n);
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            cur += sum[i];
            ans[i] = cur;
        }
        return ans;
    }
};