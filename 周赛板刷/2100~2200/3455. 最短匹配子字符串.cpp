#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        if (!item.empty())
            result.push_back(item);
    }
    return result;
}

vector<int> build_lps(string p) {
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
// returns matches in vector ans in 0-indexed
vector<int> kmp(vector<int> lps, string s, string p) {
    int psz = p.size(), sz = s.size();
    int j = 0;
    vector<int> ans;
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
    int shortestMatchingSubstring(string s, string p) {
        vector<string> words = split(p, '*');
        int m = words.size(), n = s.size();
        if (m == 0) return 0;
        vector<vector<int>> match_pos(m);
        for (int i = 0; i < m; ++i) {
            vector<int> lps = build_lps(words[i]);
            vector<int> pos = kmp(lps, s, words[i]);
            match_pos[i] = pos;
            if (pos.empty()) return -1;
        }
        if (m == 1) {
            return words[0].size();
        }
        else if (m == 2) {
            vector<int> last(n, -1);
            int j = match_pos[1].size() - 1;
            for (int i = match_pos[1][j]; i >= 0; --i) {
                if (j >= 0 && i == match_pos[1][j]) {
                    last[i] = match_pos[1][j];
                    j--;
                }
                else {
                    last[i] = match_pos[1][j+1];
                }
            }
            int ans = inf;
            for (int p : match_pos[0]) {
                if (p + words[0].size() >= n || last[p + words[0].size()] == -1) break;
                ans = min(ans, last[p + words[0].size()] + (int)words[1].size() - p);
            }
            return ans == inf ? -1 : ans;
        }
        vector<int> pre(n, -1), suf(n, -1);
        int j = 0, ans = inf;
        for (int i = match_pos[0][0]; i < n; ++i) {
            if (j < match_pos[0].size() && i == match_pos[0][j]) {
                pre[i] = match_pos[0][j];
                j++;
            }
            else {
                pre[i] = match_pos[0][j-1];
            }
        }
        j = match_pos[2].size() - 1;
        for (int i = match_pos[2][j]; i >= 0; --i) {
            if (j >= 0 && i == match_pos[2][j]) {
                suf[i] = match_pos[2][j];
                j--;
            }
            else {
                suf[i] = match_pos[2][j+1];
            }
        }
        for (int p : match_pos[1]) {
            // p - words[0].size()
            if (p - (int)words[0].size() < 0 || pre[p - words[0].size()] == -1) continue;
            if (p + (int)words[1].size() >= n || suf[p + words[1].size()] == -1) continue;
            // [pre[p - words[0].size()], suf[p + words[1].size()] + words[2].size())
            ans = min(ans, suf[p + words[1].size()] + (int)words[2].size() - pre[p - words[0].size()]);
        }
        return ans == inf ? -1 : ans;
    }
};