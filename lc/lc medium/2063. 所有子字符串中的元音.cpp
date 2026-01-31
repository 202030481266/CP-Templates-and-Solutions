#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    long long countVowels(string word) {
        int n = word.size();
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (word[i - 1] == 'a' || word[i - 1] == 'e' || word[i - 1] == 'i' || word[i - 1] == 'o' || word[i - 1] == 'u') {
                // (0, i], [i, n+1)
                ans += 1ll * i * (n + 1 - i);
            }
        }
        return ans;
    }
};