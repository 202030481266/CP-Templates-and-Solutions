#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Graph {
    int V; // 顶点数
    vector<vector<int>> adj; // 邻接表

public:
    Graph(int V) : V(V), adj(V) {}

    // 添加边
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // 找到所有环
    void findCycles(vector<vector<int>>& cycles) {
        for (int start = 0; start < V; ++start) {
            vector<int> path;
            bitset<26> visited; // 使用位掩码记录访问状态
            dfsFindCycles(start, start, path, visited, cycles);
        }
    }

private:
    // 辅助函数：DFS 查找环
    void dfsFindCycles(int start, int u, vector<int>& path, bitset<26>& visited, vector<vector<int>>& cycles) {
        path.push_back(u);
        visited.set(u);

        for (int v : adj[u]) {
            if (v == start && path.size() > 1) { // 找到环
                cycles.push_back(path);
            } else if (!visited.test(v)) { // 如果节点未被访问
                dfsFindCycles(start, v, path, visited, cycles);
            }
        }

        path.pop_back();
        visited.reset(u);
    }
};

int edge[26][26];

class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        // 结论：对于一个环来说，最好的方法就是有且只有一个点的出现次数为2
        // 答案就是找到最少的点使得出现次数为2的点数最少
        Graph g(26);
        vector<int> vis(26);
        memset(edge, 0, sizeof edge);
        for (string& s : words) {
            int u = s[0]-'a', v = s[1]-'a';
            edge[u][v] = 1;
            vis[u] = vis[v] = 1;
        }
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (edge[i][j] && !edge[j][i]) { // 只添加有向边，保证了环的大小一定大于等于3，这会大大减少计算量
                    g.addEdge(i, j);
                }
            }
        }
        vector<vector<int>> cycles;
        g.findCycles(cycles);
        vector<int> id;
        vector<int> dfn(26);
        vector<int> in(26);
        for (auto& cycle : cycles) {
            for (int& v : cycle) {
                in[v] = 1;
            }
        }
        for (string& s : words) {
            if (s[0] == s[1]) { // 自环
                in[s[0]-'a'] = 1;
                cycles.push_back({s[0]-'a'});
            }
        }
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (edge[i][j] && edge[j][i]) { // 双元环
                    in[i] = in[j] = 1;
                    cycles.push_back({i, j});
                }
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (in[i]) id.push_back(i);
        }
        int n = id.size();
        for (int i = 0; i < n; ++i) {
            dfn[id[i]] = i;
        }
        unordered_set<int> cs;
        for (auto& cycle: cycles) {
            int c = 0;
            for (int& v : cycle) {
                c |= 1<<dfn[v];
            }
            cs.insert(c);
        }
        // 找到最小的覆盖所有的环的点集
        vector<vector<int>> ans;
        vector<bool> dp(1<<n, true);
        int mn = inf;
        for (int i = 0; i < (1<<n); ++i) {
            for (int j : cs) {
                if ((i & j) == 0) {
                    dp[i] = false;
                    break;
                }
            }
            if (dp[i]) {
                mn = min(mn, __builtin_popcount(i));
            }   
        }
        for (int i = 0; i < (1<<n); ++i) {
            if (dp[i] && __builtin_popcount(i) == mn) {
                vector<int> tmp(26);
                for (int j = 0; j < n; ++j) {
                    if ((i>>j)&1) {
                        tmp[id[j]] = 2;
                    }
                    else tmp[id[j]] = 1;
                }
                for (int j = 0; j < 26; ++j) {
                    if (vis[j] && !tmp[j]) tmp[j] = 1;
                }
                ans.push_back(tmp);
            }
        }
        return ans;
    }
};

// 理论上来说上面这个算法复杂度很高才对，但是构造大量环的竞赛图非常困难，所以这个算法跑的也是飞快
// 正难则反，反正出现的次数都是1或者2，所有我们可以去找出现1次的数量的点，然后判断是否有环，判断环算法复杂度比找到所有的环要低很多
// 下面是暴力枚举 + 判断环的做法，类似的思想，不过是寻找所有只出现1次的字符的集合，而这些点构造的子图一定是无环的

class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        // 收集有哪些字母，同时建图
        int all = 0;
        vector<int> g[26]{};
        for (auto& s : words) {
            int x = s[0] - 'a', y = s[1] - 'a';
            all |= (1 << x) | (1 << y);
            g[x].push_back(y);
        }

        // 判断是否有环
        auto has_cycle = [&](int sub) -> bool {
            int color[26]{};
            auto dfs = [&](this auto&& dfs, int x) -> bool {
                color[x] = 1;
                for (int y : g[x]) {
                    // 只遍历不在 sub 中的字母
                    if (sub >> y & 1) {
                        continue;
                    }
                    if (color[y] == 1 || color[y] == 0 && dfs(y)) {
                        return true;
                    }
                }
                color[x] = 2;
                return false;
            };
            for (int i = 0; i < 26; i++) {
                // 只遍历不在 sub 中的字母
                if (color[i] == 0 && (sub >> i & 1) == 0 && dfs(i)) {
                    return true;
                }
            }
            return false;
        };

        unordered_set<int> st;
        int min_size = INT_MAX;
        // 枚举 all 的所有子集 sub
        int sub = all;
        do {
            int size = popcount((unsigned) sub);
            // 剪枝：如果 size > min_size 就不需要判断了
            if (size <= min_size && !has_cycle(sub)) {
                if (size < min_size) {
                    min_size = size;
                    st.clear();
                }
                st.insert(sub);
            }
            sub = (sub - 1) & all;
        } while (sub != all);

        vector<vector<int>> ans;
        for (int sub : st) {
            vector<int> cnt(26);
            for (int i = 0; i < 26; i++) {
                cnt[i] = (all >> i & 1) + (sub >> i & 1);
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};