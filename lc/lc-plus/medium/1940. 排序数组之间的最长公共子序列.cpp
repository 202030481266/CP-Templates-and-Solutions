#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> longestCommonSubsequence(vector<vector<int>>& arrays) {
        int n = arrays.size();

        int mx = 0;
        for (int i = 0; i < n; ++i)
            for (int v : arrays[i]) mx=max(mx, v);

        vector<int> cnt(mx+1);
        for (int i = 0; i < n; ++i)
            for (int v : arrays[i]) cnt[v]++;
        
        vector<int> ans;
        for (int i = 1; i <= mx; ++i)
            if (cnt[i] == n) ans.push_back(i);
        return ans;
    }
};