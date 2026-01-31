#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;
static constexpr int maxv = 1000005;

int dis[maxn];
int isprime[maxv];
bool flag;

void init() {
    for (int i = 2; i < maxv; ++i) isprime[i] = 1;
    for (int i = 2; i * i < maxv; ++i) {
        if (isprime[i]) {
            for (int j = i * i; j < maxv; j += i) {
                isprime[j] = 0;
            }
        }
    }
}

vector<int> g[maxv];
int vis[maxv];

class Solution {
public:
    int minJumps(vector<int>& nums) {
        if (!flag) {
            init();
            flag = true;
        }
        int n = nums.size();
        for (int i = 1; i < n; ++i) {
            g[nums[i]].push_back(i);
        }
        for (int i = 0; i < n; ++i) dis[i] = inf;
        queue<int> q;
        q.push(0);
        dis[0] = 0;
        int mx = *max_element(nums.begin(), nums.end());
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == n - 1) break;
            if (u + 1 < n && dis[u + 1] > dis[u] + 1) {
                dis[u + 1] = dis[u] + 1;
                q.push(u + 1);
            }
            if (u - 1 >= 0 && dis[u - 1] > dis[u] + 1) {
                dis[u - 1] = dis[u] + 1;
                q.push(u - 1);
            }
            if (isprime[nums[u]] && !vis[nums[u]]) {
                vis[nums[u]] = 1;
                for (int i = nums[u]; i <= mx; i += nums[u]) {
                    for (int v : g[i]) {
                        if (dis[v] > dis[u] + 1) {
                            dis[v] = dis[u] + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
        for (int v : nums) { // clear data
            vis[v] = 0;
            g[v].clear();
        }
        return dis[n - 1];
    }
};