#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 100007;
int res = 0, a[maxn], c[maxn], n;

void msort(int l, int r, int x) {
    if (l == r) return;
    int mid = (l + r) / 2, lp = l, rp = mid + 1;
    msort(l, mid, x);
    msort(mid + 1, r, x);
    for (int i = l, j = mid + 1, k = mid + 1; i <= mid; ++i) {
        while (j <= r && a[j] < a[i] - x) ++j;
        while (k <= r && a[k] < a[i]) ++k;
        if (j < k) res += k - j;
    }
    int p = l;
    while (lp <= mid && rp <= r) {
        if (a[lp] <= a[rp]) c[p++] = a[lp++];
        else c[p++] = a[rp++];
    }
    while (lp <= mid) c[p++] = a[lp++];
    while (rp <= r)  c[p++] = a[rp++];
    for (int i = l; i <= r; ++i) a[i] = c[i];
}

bool check(const vector<int>& nums, int x, int th) {
    for (int i = 1; i <= n; ++i) a[i] = nums[i-1];
    res = 0;
    msort(1, n, x);
    return res >= th;
}

class Solution {
public:
    int minThreshold(vector<int>& nums, int k) {
        n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        int mn = *min_element(nums.begin(), nums.end());
        int l = 0, r = mx - mn + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(nums, mid, k)) r = mid;
            else l = mid;
        }
        return r == mx - mn + 1 ? -1 : r;
    }
};