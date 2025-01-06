#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// Z algrorithm

const int maxn = 5007;
int arr[maxn], a[maxn];

void Z(vector<int>& b, int start, int z[]) {
    int n = b.size();
    z[0] = n-start; // [start, n)
    for (int i = start + 1, c = start + 1, r = start + 1; i < n; ++i) {
        int len = (i < r ? min(r - i, z[i - c]) : 0);
        while (i + len < n && b[i + len] == b[len + start]) ++len;
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i-start] = len;
    }
}
class Solution {
public:
    int beautifulSplits(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        Z(nums, 0, arr);
        int ans = 0;
        for (int i = 1; i < n-1; ++i) {
            // [0, i)
            if (arr[i] >= i) {
                ans += n-i-i;
                // 这里仍然需要检查
                Z(nums, i, a);
                for (int j = i+1; j < min(n,2*i); ++j) {
                    if (a[j-i] >= j-i) ++ans;
                }
            }
            else {
                Z(nums, i, a);
                for (int j = i+1; j < n; ++j) {
                    // [i, j)
                    if (a[j-i] >= j-i) ++ans;
                }
            }
        }
        return ans;
    }
};