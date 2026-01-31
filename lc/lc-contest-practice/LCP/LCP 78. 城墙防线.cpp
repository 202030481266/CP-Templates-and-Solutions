#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int rampartDefensiveLine(vector<vector<int>>& rampart) {
        int n = rampart.size();
        int l = -1, r = inf;
        vector<int> a;
        for (int i = 1; i < n; ++i) {
            a.push_back(rampart[i][0] - rampart[i-1][1]);
        }
        for (int i = 1; i < a.size(); ++i) {
            r = min(r, a[i]+a[i-1]+1);
        }
        auto check = [&](int val) -> bool {
            int pre = a[0];
            for (int i = 1; i < a.size(); ++i) {
                if (pre + a[i] < val) {
                    return false;
                }
                pre = a[i] - max(0, val - pre);
            }
            return true;
        };
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) l = mid;
            else r = mid;
        }
        return l;
    }
};