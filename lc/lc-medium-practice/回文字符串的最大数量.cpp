#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        int n = words.size();
        vector<int> cnt(26, 0);
        vector<int> x, y;
        for (string& s : words) {
            for (char& c : s) ++cnt[c - 'a'];
            int m = s.size();
            if (m & 1) x.push_back(m);
            else y.push_back(m);
        }
        // 贪心算法，首先需要判断偶数和奇数的字符串有多少
        int sum = 0, odd = 0;
        for (int v : cnt) {
            if (v & 1) ++odd;
            sum += v / 2; 
        }
        // 偶数长度
        sort(y.begin(), y.end());
        sort(x.begin(), x.end());
        // 枚举其中的奇数长度字符串
        int ans = 0, p = y.size() - 1, s = accumulate(y.begin(), y.end(), 0);
        while (p >= 0 && s / 2 > sum) {
            s -= y[p];
            --p;
        }
        ans = p + 1;
        for (int i = 0; i < x.size(); ++i) {
            if (odd) {
                --odd;
            }
            else if (sum) {
                --sum;
                odd += 1;
            }
            else break;
            if (sum < x[i] / 2) break;
            sum -= x[i] / 2;
            while (p >= 0 && s / 2 > sum) {
                s -= y[p];
                --p;
            }
            ans = max(ans, p + i + 2); // [0, p] + [0, i]
        }
        return ans;
    }
};
