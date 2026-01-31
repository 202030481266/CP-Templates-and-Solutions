#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAnagramLength(string s) {
        vector<int> cnt(26);
        for (char& ch : s) {
            ++cnt[ch-'a'];
        }
        int g = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] > 0) {
                g = gcd(g, cnt[i]);
            }
        }
        int n = s.size(), mn = n / g;
        vector sum(26, vector<int>(n+1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                sum[j][i+1] = sum[j][i] + (s[i] == j+'a');
            }
        }
        for (int f = g; f > 1; --f) {
            if (g % f == 0) {
                int k = n / f;
                bool flag = true;
                for (int i = 0; i + k - 1 < n; i += k) { // [i,i+k-1]
                    for (int j = 0; j < 26; ++j) {
                        if (sum[j][i+k] - sum[j][i] != cnt[j] / f) {
                            flag = false;
                            break;
                        }
                    }
                    if(!flag) break;
                }
                if (flag) return k;
            }
        }
        return n;
    }
};
