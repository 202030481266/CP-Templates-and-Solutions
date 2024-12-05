#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
private:
    vector<vector<int>> g, G;
    vector<vector<int>> stack;
    vector<int> ans, parent;
    string str;
    
    void rebuild(int u) {
        int val = str[u] - 'a';
        if (stack[val].empty()) {
            if (u != 0) {
                G[parent[u]].push_back(u);
            }
        } else {
            int fa = stack[val].back();
            G[fa].push_back(u);
        }
        stack[val].push_back(u);
        for (int v : g[u]) {
            rebuild(v);
        }
        stack[val].pop_back();
    }
    
    void dfs(int u) {
        ans[u] = 1;
        for (int v : G[u]) {
            dfs(v);
            ans[u] += ans[v];
        }
    }
    
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        this->parent = parent;
        g.resize(n);
        G.resize(n);
        stack.resize(26);
        ans.resize(n);
        str = s;
        
        // 构建初始树
        for (int i = 1; i < n; ++i) {
            g[parent[i]].push_back(i);
        }
        
        // 重构树并计算大小
        rebuild(0);
        dfs(0);
        return ans;
    }
};