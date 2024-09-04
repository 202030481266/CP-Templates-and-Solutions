#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;



class Solution {
public:
    vector<vector<int>> findMaximalUncoveredRanges(int n, vector<vector<int>>& ranges) {
        vector<pii> arr;
        for(auto p : ranges) {
            int l = p[0], r = p[1];
            arr.push_back({l,1});
            arr.push_back({r,-1});
        }
        sort(arr.begin(), arr.end());
        int sum = 0;
        vector<vector<int>> ans;
        int pre = 0;
        for (auto [x, y] : arr) {
            if (sum == 0 && x-1 >= pre) {
                // [pre, x)
                ans.push_back({pre, x-1});
            }
            pre = -1; // 没有起点
            sum += y;
            if (sum == 0) pre = x+1; // 新的起点
        }
        if (pre != -1 && n-1 >= pre) ans.push_back({pre, n-1});
        return ans;
    }
};