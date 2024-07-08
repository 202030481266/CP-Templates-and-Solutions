// 讲解视频： https://www.bilibili.com/video/BV1Sy421a78C
// 源代码仓库：https://github.com/algorithmzuo/algorithm-journey
// 题目：https://www.luogu.com.cn/problem/P5357
// AC自动机的优化都是来源于fail树的思想，调整后缀

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 静态版本 AC自动机
struct AC
{
    int N, P;
    const int A = 26;
    vector <vector <int>> next; // Trie tree
    vector <int> link, out_link, cnt; // fail 指针
    vector <vector <int>> out; // 每个节点对应的模式串编号
    vector <vector <int>> g; // fail 树
    AC(): N(0), P(0)
    {
        node();
    }
    int node() // 构造初始化节点
    {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        cnt.emplace_back(0);
        out.emplace_back(0);
        g.emplace_back(0);
        return N++;
    }
    inline int get (char c)
    {
        return c - 'a';
    }
    int add_pattern (const string T) // 建立trie树
    {
        int u = 0;
        for (auto c : T)
        {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        if (out[u].empty()) { // 保证每个模式串只被加入一次
            out[u].push_back(P++);
        }
        return u;
    }
    void compute() // 建立fail指针，使用BFS
    {
        queue <int> q;
        for (q.push(0); !q.empty();)
        {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c)
            {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c]; // 这里做了一个fail优化
                else
                {
                    link[v] = u ? next[link[u]][c] : 0; // 指向原点或者父亲的fail指针
                    // out_link指向失配后的最长的后缀子串
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    void build_graph() {
        for (int i = 1; i < N; i++) { // 0是原点
            g[link[i]].push_back(i);
        }
    }
    void dfs(int u) { // 离线计算出现总次数
        for (auto& v : g[u]) {
            dfs(v);
            cnt[u] += cnt[v];
        }
    }
    int advance (int u, char c) // 搜索，就是在线的Trie树上走
    {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; 
    cin >> n;
    AC aho;
    string s;
    vector<int> index(n);
    for (int i = 0; i < n; i++) {
        cin >> s;
        index[i] = aho.add_pattern(s);
    }
    aho.compute();
    int cur = 0;
    cin >> s; // 文本串
    for (auto& c : s) {
        cur = aho.advance(cur, c);
        aho.cnt[cur]++;
    }
    aho.build_graph();
    aho.dfs(0);
    for (int i = 0; i < n; ++i) {
        cout << aho.cnt[index[i]] << '\n';
    }
    return 0;
}