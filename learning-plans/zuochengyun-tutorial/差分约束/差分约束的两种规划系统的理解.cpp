// https://www.luogu.com.cn/problem/P2474
// 此题是一道非常好的题目，解释了差分约束的本质性的东西
// 这道题目是一道Floyd的算法题目，floyd的规划过程解释了差分约束的本质的东西
// 但是使用SPFA做一遍，我觉得才真正理解了差分约束

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

vector<pii> g1[100],g2[100]; 
int dmin[100][100], dmax[100][100];
int vis[100], n, a,b;

void spfa() {
    // 对于每一个点出发一次，求解最大的差分
    for (int i = 1; i <= n; ++i) {
        memset(dmax[i], 0x3f, sizeof(dmax[i]));
        dmax[i][i] = 0;
        vis[i] = 1;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (pii& e : g1[u]) {
                int v = e.first, w = e.second;
                if (dmax[i][v] > dmax[i][u] + w) { // u + w >= v, v = min(u + w)
                    dmax[i][v] = dmax[i][u] + w;
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    // 对于每一个点出发一次，求解最小的差分
    for (int i = 1; i <= n; ++i) {
        memset(dmin[i], -0x3f, sizeof(dmin[i]));
        dmin[i][i] = 0;
        vis[i] = 1;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (pii& e : g2[u]) {
                int v = e.first, w = e.second;
                if (dmin[i][v] < dmin[i][u] + w) { // u + w <= v, v = max(u + w)
                    dmin[i][v] = dmin[i][u] + w;
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> a >> b;
    
    vector<string> s(n+1);
    for(int i=1; i<=n; ++i){
        cin >> s[i];
    }
    
    // 构建图
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i][j-1] == '+') {
                // i > j, i >= j + 1
                // i - j <= 2, i <= j + 2
                g1[j].push_back({i, 2});
                g2[j].push_back({i, 1});
            }
            else if (s[i][j-1] == '-') {
                // i < j, i <= j - 1
                // i >= j - 2 
                g1[j].push_back({i, -1});
                g2[j].push_back({i, -2});
            }
            else if (s[i][j-1] == '=') {
                // i == j, i <= j + 0, i >= j + 0
                g1[j].push_back({i, 0});
                g2[j].push_back({i, 0});
            }
            else {
                // i <= j + 2, i >= j - 2
                g1[j].push_back({i, 2});
                g2[j].push_back({i, -2});
            }
        }
    }
    
    spfa();
    
    // Floyd-Warshall adaptation
    // for(int k=1; k<=n; ++k){
    //     for(int i=1; i<=n; ++i){
    //         for(int j=1; j<=n; ++j){
    //             dmin[i][j] = max(dmin[i][j], dmin[i][k] + dmin[k][j]);
    //             dmax[i][j] = min(dmax[i][j], dmax[i][k] + dmax[k][j]);
    //         }
    //     }
    // }
    
    int ans1=0, ans2=0, ans3=0;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<i; ++j){
            if(i == a || i == b || j == a || j == b) continue;
            
            // Check if left side is always heavier
            if(dmin[a][i] > dmax[j][b] || dmin[a][j] > dmax[i][b]){
                ans1++;
            }
            
            // Check if right side is always heavier
            if(dmax[a][i] < dmin[j][b] || dmax[a][j] < dmin[i][b]){
                ans3++;
            }
            
            // Check if sides are always balanced
            bool balanced1 = (dmin[a][i] == dmax[a][i]) && (dmin[j][b] == dmax[j][b]) && (dmin[a][i] == dmin[j][b]);
            bool balanced2 = (dmin[b][i] == dmax[b][i]) && (dmin[j][a] == dmax[j][a]) && (dmin[b][i] == dmin[j][a]);
            if(balanced1 || balanced2){
                ans2++;
            }
        }
    }
    
    cout << ans3 << " " << ans2 << " " << ans1;
}
