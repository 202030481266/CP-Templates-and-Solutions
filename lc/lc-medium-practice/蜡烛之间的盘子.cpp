#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> left(n), right(n), sum(n);
        int last = -1;
        for (int i = 0 ; i < n; ++i) {
            if (s[i] == '|') last = i;
            left[i] = last;
        }
        last = n;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '|') last = i;
            right[i] = last;
        }
        sum[0] = (s[0] == '*' ? 1 : 0);
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i-1] + (s[i] == '*' ? 1 : 0);
        }
        vector<int> ans;
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            l = right[l];
            r = left[r];
            if (l >= r) {
                ans.push_back(0);
            }
            else {
                ans.push_back(sum[r] - sum[l]);
            }
        }
        return ans;
    }
};