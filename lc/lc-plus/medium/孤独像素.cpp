#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        int n = picture.size(), m = picture[0].size();
        vector<int> row(n), col(m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (picture[i][j] == 'B') {
                    ++row[i];
                    ++col[j];
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (picture[i][j] =='B' && row[i] == 1 && col[j] == 1) ++ans;
            }
        }
        return ans;
    }
};