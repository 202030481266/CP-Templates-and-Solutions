#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        vector<int> ans;
        while (n) {
            ans.push_back(n % 10);
            n /= 10;
        }
        vector<int> x, y;
        vector<int> bro(ans.size());
        for (int i = 0; i < ans.size(); ++i) {
            ans[i] += bro[i];
            if (i == ans.size() - 1) {
                if (ans[i]) {
                    x.push_back(1);
                    y.push_back(ans[i] - 1);
                }
            }
            else {
                if (ans[i] < 2) {
                    // can't split into 2 numbers
                    assert(i + 1 < ans.size());
                    bro[i + 1] -= 1;
                    ans[i] += 10;
                }
                if (ans[i] > 9) {
                    x.push_back(9);
                    y.push_back(ans[i] - 9);
                }
                else {
                    x.push_back(1);
                    y.push_back(ans[i] - 1);
                }
            }
        }
        int a = 0, b = 0;
        for (int i = x.size() - 1; i >= 0; --i) a = a * 10 + x[i];
        for (int i = y.size() - 1; i >= 0; --i) b = b * 10 + y[i];
        return {a, b};
    }
};