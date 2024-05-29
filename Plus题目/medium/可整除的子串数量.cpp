#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int countDivisibleSubstrings(string word) {
        int n = word.size(), sum[n+1];
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < n; ++i) {
            int t = (word[i]-'a');
            sum[i+1] = sum[i] + (t <= 1 ? 1 : (t-2)/3+2);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; ++j) {
                if ((sum[i]-sum[j-1]) % (i-j+1) == 0) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};