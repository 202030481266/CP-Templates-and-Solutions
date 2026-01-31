#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int removeAlmostEqualCharacters(string word) {
        int n = word.size(), ans = 0;
        for (int i = 1; i < n; ++i) {
            if (abs(word[i] - word[i-1]) <= 1) {
                if  (i+1 == n) {
                    ans++;
                }
                else {
                    ans++;
                    i++;
                }
            }
        }
        return ans;
    }
};