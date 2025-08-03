#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 10005;
static constexpr int maxb = 105;

int a[maxn];
int pre[maxb][maxn], mx[maxb][maxb];
int bl[maxb], br[maxb], belong[maxn], cnt[maxn];

class Solution {
public:
    vector<int> subarrayMajority(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> arr(nums.begin(), nums.end());
        ranges::sort(arr);
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        for (int i = 1; i <= n; ++i) {
            a[i] = lower_bound(arr.begin(), arr.end(), nums[i-1]) - arr.begin() + 1;
        }
        int blen = (int)sqrt(n), N = (n + blen - 1) / blen, m = arr.size();
        for (int i = 1; i <= N; ++i) {
            bl[i] = (i - 1) * blen + 1;
            br[i] = min(n, i * blen);
        }
        for (int i = 1; i <= n; ++i) {
            belong[i] = (i - 1) / blen + 1;
        }
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= m; ++j) pre[i][j] = pre[i-1][j];
            for (int j = bl[i]; j <= br[i]; ++j) {
                pre[i][a[j]]++;
            }
        }
        for (int i = 1; i <= N; ++i) { // init
            for (int j = i; j <= N; ++j) {
                mx[i][j] = 0;
            }
        }
        for (int i = 1; i <= N; ++i) {
            for (int j = i; j <= N; ++j) {
                mx[i][j] = mx[i][j-1];
                int mx_cnt = pre[j][mx[i][j]] - pre[i-1][mx[i][j]];
                for (int k = bl[j]; k <= br[j]; ++k) {
                    int cur = pre[j][a[k]] - pre[i-1][a[k]];
                    if (cur > mx_cnt) {
                        mx_cnt = cur;
                        mx[i][j] = a[k];
                    }
                    else if (cur == mx_cnt && a[k] < mx[i][j]) {
                        mx[i][j] = a[k];
                    }
                }
            }
        }
        vector<int> ans;
        for (auto& q : queries) {
            int l = q[0] + 1, r = q[1] + 1;
            if (belong[l] == belong[r] || belong[l] == belong[r] - 1) {
                int res = 0;
                for (int i = l; i <= r; ++i) {
                    ++cnt[a[i]];
                    if (cnt[a[i]] > cnt[res]) {
                        res = a[i];
                    }
                    else if (cnt[a[i]] == cnt[res] && a[i] < res) {
                        res = a[i];
                    }
                }
                if (cnt[res] >= q[2]) ans.push_back(arr[res - 1]);
                else ans.push_back(-1);
                for (int i = l; i <= r; ++i) cnt[a[i]] = 0;
            }
            else {
                int L = belong[l] + 1, R = belong[r] - 1, res = mx[L][R];
                for (int i = l; i <= br[belong[l]]; ++i) {
                    ++cnt[a[i]];
                    int cur = cnt[a[i]] + pre[R][a[i]] - pre[L - 1][a[i]];
                    if (cur > cnt[res] + pre[R][res] - pre[L - 1][res]) {
                        res = a[i];
                    }
                    else if (cur == cnt[res] + pre[R][res] - pre[L - 1][res] && a[i] < res) {
                        res = a[i];
                    }
                }
                for (int i = bl[belong[r]]; i <= r; ++i) {
                    ++cnt[a[i]];
                    int cur = cnt[a[i]] + pre[R][a[i]] - pre[L - 1][a[i]];
                    if (cur > cnt[res] + pre[R][res] - pre[L - 1][res]) {
                        res = a[i];
                    }
                    else if (cur == cnt[res] + pre[R][res] - pre[L - 1][res] && a[i] < res) {
                        res = a[i];
                    }
                }
                if (cnt[res] + pre[R][res] - pre[L - 1][res] >= q[2]) ans.push_back(arr[res - 1]);
                else ans.push_back(-1);
                for (int i = l; i <= br[belong[l]]; ++i) cnt[a[i]] = 0;
                for (int i = bl[belong[r]]; i <= r; ++i) cnt[a[i]] = 0;
            }
        }
        return ans;
    }
};