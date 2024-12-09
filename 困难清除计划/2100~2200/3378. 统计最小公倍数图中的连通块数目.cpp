#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 200001;
int cnt[maxn], fa[maxn];

// 没想到并查集跑到了双百！
int find(int i) {
    return fa[i] == i ? i : fa[i] = find(fa[i]);
}

void merge(int i, int j) {
    int fi = find(i), fj = find(j);
    if (fi == fj) return;
    // 统一将大的父节点指向小的父节点
    if (fi < fj) {
        fa[fj] = fi;
    } else {
        fa[fi] = fj;
    }
}

class Solution {
public:
    int countComponents(vector<int>& nums, int threshold) {
        int n = nums.size(), ans = 0, mx = 0;
        memset(cnt, 0, sizeof(cnt));
        for (int v : nums) {
            if (v > threshold) ++ans;
            else {
                mx = max(mx, v);
                cnt[v] = 1;
            }
        }
        for (int i = 1; i <= mx; ++i) fa[i] = i;
        for (int i = 1; i <= mx; ++i) {
            int mn = inf;
            for (int j = i; j <= mx; j += i) {
                if (cnt[j]) {
                    if (mn == inf) {
                        mn = j;
                    }
                    else {
                        if (1ll*j*mn/i <= threshold) {
                            merge(j,mn);
                        }
                        else break;
                    }
                }
            }
        }
        for (int v : nums) {
            if (v <= threshold && find(v) == v) ++ans; 
        }
        return ans;
    }
};