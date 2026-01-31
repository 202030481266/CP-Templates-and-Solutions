#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size(), cnt0 = 0;
        for (char c : s) {
            if (c == '0') ++cnt0;
        }
        // easy special judge
        if (cnt0 == 0) return 0;
        if (n < k) return -1;
        if (n == k) return cnt0 == n ? 1 : -1;
        if (k % 2 == 0 && (cnt0 & 1)) return -1;
        if (cnt0 == k) return 1;
        // hard part
        auto cal = [&](int x) -> pii { // 这个函数是证明导出的是连续区间的关键
            int l = k - 2 * min(k, x), r = min(k, n - x) * 2 - k;
            return {x + l, x + r};
        };
        int plo = k, phi = k, nlo = k, nhi = k, pr = 0, nr = 0, ans = 1, flag = 1;
        while (ans <= n) {
            if (k & 1) {
                if (cnt0 & 1) {
                    if (cnt0 >= nlo && cnt0 <= nhi) return ans;
                }
                else {
                    if (cnt0 <= nr) return ans;
                }
            }
            else {
                if (cnt0 <= nr || cnt0 >= nlo && cnt0 <= nhi) return ans;
            }
            ++ans;
            if (!flag) {
                while (pr <= nr) {
                    auto [l, r] = cal(pr);
                    nlo = min(nlo, l);
                    nhi = max(nhi, r);
                    pr += 2;
                }
            }
            else {
                while (plo >= nlo) {
                    auto [l, r] = cal(plo);
                    nr = max(nr, r);
                    plo -= 2;
                }
                while (phi <= nhi) {
                    auto [l, r] = cal(phi);
                    nr = max(nr, r);
                    phi += 2;
                }
            }
            flag ^= 1;
        }
        return ans;
    }
};