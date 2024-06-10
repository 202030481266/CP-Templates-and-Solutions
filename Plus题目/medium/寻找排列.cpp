#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    // 摆动序列的方法
    vector<int> findPermutation(string s) {
        int n = s.size() + 1;
        vector<int> ans;
        int i = 1, p = 0;
        while (i <= n && p < s.size()) {
            if (s[p] == 'I') {
                ans.push_back(i++);
                p += 1;
            }
            else {
                int j = p;
                while (j < s.size() && s[j] == 'D') j++;
                // [p, j), i,i+1,i+2..i+m
                int m = j - p;
                for (int k = i+m; k >= i; k--) {
                    ans.push_back(k);
                }
                i = i+m+1;
                p = j+1;
            }
        }
        if (i <= n) ans.push_back(i);
        return ans;
    }
};