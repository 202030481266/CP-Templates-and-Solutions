// https://codeforces.com/problemset/problem/385/B
#include <bits/stdc++.h>
using namespace std;

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
            // pattern found in string s at position i-psz+1
            ans.push_back(i - psz + 1);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    string p = "bear";
    cin >> s;
    auto lps = build_lps(p);
    auto matches = kmp(lps, s, p);
    long long ans = 0;
    long long n = s.size();
    int m = matches.size();
    for (int i = 0; i < m; ++i) {
        if (i + 1 < m) {
            // [0, matches[i]] ... [matches[i]+3, matches[i+1]+3)
            ans += (matches[i] + 1) * (matches[i + 1] - matches[i]);
        }
        else {
            // [0, matches[i]] ... [matches[i]+3, n)
            ans += (matches[i] + 1) * (n - matches[i] - 3);
        }
    }
    cout << ans << endl;
}