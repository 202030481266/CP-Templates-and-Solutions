#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        if (tokens.size() == 0) return 0;
        sort(tokens.begin(), tokens.end());
        int n = tokens.size();
        int cur = power, res = 0, ans = 0, p = n-1, l = 0;
        if (power < tokens[0]) return 0;
        // 获取当前最多分数并且保持了最大的能量
        for (int i = 0; i <= p; ++i) {
            while (l < i && p > i && cur < tokens[i]) {
                --res;
                ++l;
                cur += tokens[p--];
            }
            if (cur >= tokens[i]) {
                res++;
                cur -= tokens[i];
                if (ans < res) ans = res;
            }
        }
        return ans;
    }
};