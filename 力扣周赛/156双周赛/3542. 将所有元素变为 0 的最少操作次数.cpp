#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int r[100005];
int st[100005], ptr = 0;
int idx[100005], b[100005];
int a[100005], m = 0;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0, sum = 0;
        int mx = *max_element(nums.begin(), nums.end());
        vector<vector<int>> pos(mx+1);
        int p = 0;
        m = 0;
        while (p < n) {
            int i = p + 1;
            while (i < n && nums[i] == nums[p]) ++i;
            if (nums[p]) ++sum;
            pos[nums[p]].push_back(m);
            a[m++] = nums[p];
            p = i;
        }
        ptr = 0;
        for (int i = 0; i < m; ++i) {
            while (ptr > 0 && a[st[ptr-1]] > a[i]) {
                r[st[--ptr]] = i;
            }
            st[ptr++] = i;
        }
        for (int i = 0; i < ptr; ++i) r[st[i]] = m;
        for (int i = 0; i <= mx; ++i) idx[i] = b[i] = 0;
        for (int i = 0; i < m; ++i) {
            int v = a[i];
            if (v == 0) continue;
            while (idx[v] < (int)pos[v].size() && pos[v][idx[v]] < r[i]) {
                a[pos[v][idx[v]++]] = 0;
            }
            ++ans;
        }
        return (ans == inf ? 0 : ans);
    }
};

// 更加快的解法，思路有点难想的
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        int top = -1; // 栈顶下标（把 nums 当作栈）
        for (int x : nums) {
            while (top >= 0 && x < nums[top]) {
                top--; // 出栈
                ans++;
            }
            // 如果 x 与栈顶相同，那么 x 与栈顶可以在同一次操作中都变成 0，x 无需入栈
            if (top < 0 || x != nums[top]) {
                nums[++top] = x; // 入栈
            }
        }
        return ans + top + (nums[0] > 0);
    }
};