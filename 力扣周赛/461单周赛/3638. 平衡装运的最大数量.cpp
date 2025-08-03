#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    int maxBalancedShipments(vector<int>& weight) {
        int n = weight.size();
        int ans = 0, i = n - 1;
        while (i >= 1) {
            if (weight[i - 1] > weight[i]) {
                ++ans;
                if (i == 2) break;
                i -= 2;
            }
            else {
                --i;
            }
        }
        return ans;
    }
};