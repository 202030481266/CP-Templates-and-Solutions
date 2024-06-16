#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int target) {
        // 字符串哈希
        int n = picture.size(), m = picture[0].size();
        unordered_map<string, int> cnt;
        vector<int> col(m);
        for (int i = 0; i < n; ++i) {
            string tmp;
            for (int j = 0; j < m; ++j) {
                tmp += picture[i][j];
                if (picture[i][j] == 'B') ++col[j];
            }
            ++cnt[tmp];
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            string tmp;
            int c = 0;
            for (int j = 0; j < m; ++j) {
                tmp += picture[i][j];
                if (picture[i][j] == 'B') ++c;
            }
            if (cnt[tmp] == target && c == target) {
                for (int j = 0; j < m; ++j) {
                    if (picture[i][j] == 'B' && col[j] == target) {
                        ans += target;
                    }
                }
                cnt[tmp] = 0;
            }
        }
        return ans;
    }
};