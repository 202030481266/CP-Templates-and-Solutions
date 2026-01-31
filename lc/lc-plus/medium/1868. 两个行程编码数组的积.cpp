#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<vector<int>> findRLEArray(vector<vector<int>>& a, vector<vector<int>>& b) {
        int i = 0, j = 0, n = a.size(), m = b.size();
        int pre = -1, pi = pre + a[i][1], pj = pre + b[j][1];
        vector<vector<int>> res;
        vector<int> tmp;
        while (i < n || j < m) {
            int mul = a[i][0] * b[j][0];
            if (pi == pj) {
                res.push_back({pre, pi});
                ++i;
                ++j;
                pre = pi;
                if (i < n) pi = pi + a[i][1];
                if (j < m) pj = pj + b[j][1];
            }
            else if (pi > pj) {
                res.push_back({pre, pj});
                ++j;
                pre = pj;
                if (j < m) pj = pj + b[j][1];
            }
            else {
                res.push_back({pre, pi});
                ++i;
                pre = pi;
                if (i < n) pi = pi + a[i][1];
            }
            tmp.push_back(mul);
        }
        // merge
        j = 0;
        vector<vector<int>> ans;
        for (i = 0; i < res.size(); ++i) {
            if (tmp[i] != tmp[j]) {
                // [j, i-1]
                // (res[j][0], res[i-1][1]]
                int len = res[i-1][1] - res[j][0];
                ans.push_back({tmp[j], len});
                j = i;
            }
        }
        ans.push_back({tmp.back(), pi-res[j][0]});
        return ans;
    }
};