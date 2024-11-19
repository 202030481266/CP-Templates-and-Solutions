#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int dis[510];

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        memset(dis, 0x3f, sizeof(dis));
        vector<int> ans;
        vector<int> g[n];
        dis[0] = 0;
        for (int i = 1; i < n; ++i) {
            g[i-1].push_back(i);
            dis[i] = i;
        }
        for (auto e : queries) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            queue<int> q;
            q.push(u);
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                for (int x : g[cur]) {
                    if (dis[x]>dis[cur]+1) {
                        dis[x]=dis[cur]+1;
                        q.push(x);
                    }
                }
            }
            ans.push_back(dis[n-1]);

        }
        return ans;
    }
};