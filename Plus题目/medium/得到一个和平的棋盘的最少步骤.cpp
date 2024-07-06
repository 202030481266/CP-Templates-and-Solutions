#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int minMoves(vector<vector<int>>& rooks) {
        int n = rooks.size();
        vector<int> x, y;
        for (auto& p : rooks) {
            x.push_back(p[0]);
            y.push_back(p[1]);
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        int ans = 0;
        for (int i = 0; i < n; ++i) ans += abs(x[i] - i) + abs(y[i] - i);
        return ans;
    }
};