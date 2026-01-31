#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int maxJump(vector<int>& stones) {
        int n = stones.size();
        if (n==3) return stones[n-1]-stones[0];
        int ans = 0, pre = stones[0];
        for (int i = 1; i < n-1; i += 2) {
            ans = max(ans, stones[i]-pre);
            pre = stones[i];
        }
        ans = max(ans, stones[n-1]-pre);
        pre = stones[0];
        for (int i = 2; i < n-1; i += 2) {
            ans = max(ans, stones[i]-pre);
            pre = stones[i];
        }
        ans = max(ans, stones[n-1]-pre);
        return ans;
    }
};