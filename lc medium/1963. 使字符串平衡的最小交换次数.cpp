#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();
        if (n == 0) return 0;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '[') ++cnt;
            else {
                if (cnt == 0) {
                    ++ans;
                    ++cnt;
                }
                else --cnt;
            }
        }
        return ans;
    }
};