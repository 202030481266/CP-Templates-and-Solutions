#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

// 很有意思的题目，环形构造很容易搞
// 也可以暴力，但是复杂度比较高，但是此题n很小

int ans[3000][2];
int ids[60];

class Solution {
public:
    vector<vector<int>> generateSchedule(int n) {
        if (n <= 4) return {};
        iota(ids, ids + n, 0);
        int tot = 0;
        if (n & 1) {
            int p = 0;
            for (int i = 0; i < n; ++i) {
                ans[++tot][0] = p;
                ans[tot][1] = (p + 1) % n;
                p = (p + 2) % n;
            }
            for (int step = 2; step < n - 1; ++step) {
                for (int i = 0; i < n; ++i) {
                    ans[++tot][0] = i;
                    ans[tot][1] = (i + step) % n;
                }
            }
            p = 1;
            for (int i = 0; i < n; ++i) {
                ans[++tot][0] = p;
                ans[tot][1] = (p + n - 1) % n;
                p = (p + 2) % n;
            }
        }
        else {
            int p = 0;
            for (int i = 0; i < n / 2; ++i) {
                ans[++tot][0] = p;
                ans[tot][1] = (p + 1) % n;
                p = (p + 2) % n;
            }
            p = 1;
            for (int i = 0; i < n / 2; ++i) {
                ans[++tot][0] = p;
                ans[tot][1] = (p + 1) % n;
                p = (p + 2) % n;
            }
            for (int step = 2; step < n - 1; ++step) {
                for (int i = 0; i < n; ++i) {
                    ans[++tot][0] = (i + 1) % n;
                    ans[tot][1] = (i + 1 + step) % n;
                }
            }
            p = 2;
            for (int i = 0; i < n / 2; ++i) {
                ans[++tot][0] = p;
                ans[tot][1] = (p + n - 1) % n;
                p = (p + 2) % n;
            }
            p = 3;
            for (int i = 0; i < n / 2; ++i) {
                ans[++tot][0] = p;
                ans[tot][1] = (p + n - 1) % n;
                p = (p + 2) % n;
            }
        }
        vector res(tot, vector<int>(2));
        for (int i = 0; i < tot; ++i) {
            res[i][0] = ans[i+1][0];
            res[i][1] = ans[i+1][1];
        }
        return res;
    }
};