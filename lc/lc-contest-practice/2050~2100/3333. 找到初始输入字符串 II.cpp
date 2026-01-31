#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;



class Solution {
public:
    int possibleStringCount(string word, int k) {
        int n = word.size(), m = 0; 
        vector<int> a;
        int l = 0;
        ll res = 1;
        for (int i = 0; i < n; ++i) {
            if (word[i] != word[l]) {
                // [l, i)
                if (i-l > 1)
                    a.push_back(i-l-1);
                res = res * (i-l) % mod;
                l = i;
                m++;
            }
        }
        if (n-l > 1)
            a.push_back(n-l-1);
        res = res * (n-l) % mod;
        m++;

        if (m >= k) return res;
        
        // dp[i] = s[i] - s[i-a[i]]
        // < k -> < k-m
        vector<ll> s(k-m+1);
        s[0] = 1;
        ll pre;
        for (int i = 0; i < a.size(); ++i) {
            pre = 0;
            for (int j = k-m-1; j >= 0; --j) {
                int up = max(0, j-a[i]);
                // [up,i-1]
                ll tmp = ((s[up] - pre) % mod + s[j+1] + mod) % mod;
                pre = s[j];
                s[j] = tmp;
            }
        }
        
        return (res - s[0] + mod) % mod;
    }
};




