#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

vector<int> build_lps(const string& p) {
    int sz = p.size();
    vector<int> lps;
    lps.assign(sz + 1, 0);
    int j = 0;
    lps[0] = 0;
    for (int i = 1; i < sz; i++) {
        while (j >= 0 && p[i] != p[j]) {
            if (j >= 1)
                j = lps[j - 1];
            else
                j = -1;
        }
        j++;
        lps[i] = j;
    }
    return lps;
}

vector<int> kmp(const vector<int>& lps, const string& s, const string& p) {
    vector<int> ans;
    int psz = p.size(), sz = s.size();
    int j = 0;
    for (int i = 0; i < sz; i++) {
        while (j >= 0 && p[j] != s[i])
            if (j >= 1)
                j = lps[j - 1];
            else
                j = -1;
        j++;
        if (j == psz) {
            j = lps[j - 1];
            ans.push_back(i - psz + 1);
        }
    }
    return ans;
}

class Solution {
public:
    int countCells(vector<vector<char>>& grid, string pattern) {
        int n = grid.size(), m = grid[0].size();
        string vertical, horizontal;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) horizontal.push_back(grid[i][j]);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) vertical.push_back(grid[j][i]);
        }
        vector<int> lps = build_lps(pattern);
        vector<int> match_v = kmp(lps, vertical, pattern);
        vector<int> match_h = kmp(lps, horizontal, pattern);
        vector<int> sum_v(n * m + 1, 0), sum_h(n * m + 1, 0);
        int len = pattern.size();
        for (int& i : match_v) {
            sum_v[i]++;
            sum_v[i + len]--;
        }
        for (int& i : match_h) {
            sum_h[i]++;
            sum_h[i + len]--;
        }
        for (int i = 1; i < n * m; ++i) {
            sum_v[i] += sum_v[i-1];
            sum_h[i] += sum_h[i-1];
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (sum_h[i * m + j] && sum_v[j * n + i]) ++ans;
            }
        }
        return ans;
    }
};