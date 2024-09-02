#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;



class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        // 滑窗
        // 2 * n
        int n = answerKey.size(), ans = 0;
        // turn into T
        auto f = [&](char c) {
            int l = 0, need = 0; 
            for (int i = 0; i < n; ++i) {
                if (answerKey[i] == c) ++need;
                while (need > k) {
                    if (answerKey[l++] == c) --need;
                }
                ans = max(ans, i-l+1);
            }
        };
        f('F');
        f('T');
        return ans;
    }
};