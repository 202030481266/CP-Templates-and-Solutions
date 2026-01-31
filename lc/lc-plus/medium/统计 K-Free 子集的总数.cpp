#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

bool flag = false;

ll p[100], f[100];

void init() {
    if (flag) return;
    flag = true;
    p[0] = 1;
    for (int i = 1; i < 55; ++i) p[i] = p[i-1] * 2;
    f[1] = 2, f[2] = 3;
    for (int i = 3; i <= 50; ++i) f[i] = f[i-1] + f[i-2];
}

class Solution {
public:
    long long countTheNumOfKFreeSubsets(vector<int>& nums, int k) {
        init();
        int n = nums.size();
        sort(nums.begin(), nums.end());
        ll ans = 1; // 2 ^ n
        vector<int> a;
        vector<bool> vis(n,false);
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            int s = nums[i], len = 1;
            for (int j = i+1; j < n; ++j) {
                if (nums[j] == s + k) {
                    ++len;
                    s = nums[j];
                    vis[j] = true;
                }
                else if (nums[j] > s + k) {
                    break;
                }
            }
            if (len > 1) a.push_back(len);
        }
        ll sum = 0;
        for (int v : a) sum += v;
        ll rem = n - sum;
        ll sub = 1;
        for (int v : a) {
            // such as v == 3, 000, 001, 010, 100 
            sub *= f[v];
        }
        return sub * p[rem];
    }
};