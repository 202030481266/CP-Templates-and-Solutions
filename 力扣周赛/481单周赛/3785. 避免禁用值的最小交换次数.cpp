#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int> >;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size();
        vector<int> arr;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == forbidden[i]) arr.push_back(nums[i]);
        }
        ranges::sort(arr);
        int m = arr.size();
        int p = 0, flag = 0, t = 0;
        while (p < m) {
            int i = p + 1;
            while (i < m && arr[i] == arr[p]) ++i;
            if (i - p > m / 2) {
                flag = p;
                t = i - p;
                break;
            }
            p = i;
        }
        if (!t) return (m + 1) / 2;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] != forbidden[i] && nums[i] != arr[flag] && forbidden[i] != arr[flag]) ++cnt;
        }
        if (cnt + m - t < t) return -1;
        return t;
    }
};