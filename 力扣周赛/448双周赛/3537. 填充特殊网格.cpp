#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    vector<vector<int>> specialGrid(int n) {
        vector ans(1<<n, vector<int>(1<<n));
        for (int i = 1, j = 0; i < (1<<n); i *= 2, j += 2) {
            // [0, (1<<n)-1]
            // [0, (1<<n)-i] , [i-1, (1<<n)-1]
            for (int x = 0; x <= i-1; ++x) {
                for (int y = (1<<n)-i; y <= (1<<n)-1; ++y) {
                    ans[x+i][y] = ans[x][y] + (1<<j);
                    ans[x+i][y-i] = ans[x][y] + (1<<j)*2;
                    ans[x][y-i] = ans[x][y] + (1<<j)*3;
                }
            }
        }
        return ans;
    }
};