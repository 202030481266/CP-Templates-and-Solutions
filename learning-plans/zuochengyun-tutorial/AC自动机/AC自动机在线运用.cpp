// 讲解视频： https://www.bilibili.com/video/BV1Sy421a78C
// 源代码仓库：https://github.com/algorithmzuo/algorithm-journey
// 题目：https://www.luogu.com.cn/problem/P3311
// AC自动机是一个很擅长在线的算法，所以一般自动机难题会考察在线的一些算法结合
// 数位DP的逐个位置选取也是一个在线的过程

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


// 预处理标记
// 静态版本 AC自动机
struct AC
{
    int N;
    const int A = 10; // 0 ~ 9
    vector <vector <int>> next; // Trie tree
    vector <int> link; // fail 指针
    vector <bool> is_end; // 判断 fail 链的祖先有没有是模式串的结尾
    AC(): N(0)
    {
        node();
    }
    int node() // 构造初始化节点
    {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        is_end.emplace_back(false);
        return N++;
    }
    inline int get (char c)
    {
        return c - '0';
    }
    int add_pattern (const string T) // 建立trie树
    {
        int u = 0;
        for (auto c : T)
        {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        is_end[u] = true;
        return u;
    }
    void compute() // 建立fail指针，使用BFS
    {
        queue <int> q;
        for (int c = 0; c < A; ++c) {
        	if (next[0][c]) q.push(next[0][c]);
        }
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c)
            {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c]; // 这里做了一个fail优化
                else
                {
                    link[v] = next[link[u]][c]; // 指向原点或者父亲的fail指针
                    // out_link指向失配后的最长的后缀子串
                    q.push(v);
                }
            }
            is_end[u] = is_end[u] || is_end[link[u]]; // 判断是否有模式串的结尾，u的fail指针已经被设置好了
        }
    }
    int advance (int u, char c) // 搜索，就是在线的Trie树上走
    {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
};

int m;
AC aho;
string N;
int dp[1210][1510];

int dfs(int p, int u, bool is_limit, bool is_num) { // 灵神的模板
    if (aho.is_end[u]) return 0; // 匹配到了模式串
    if (p == N.size()) return is_num;
    if (!is_limit && is_num && dp[p][u] > -1) return dp[p][u];
    int up = (is_limit ? N[p] - '0' : 9);
    int res = 0;
    if (!is_num) {
        res += dfs(p + 1, u, false, false); // 不填
        for (int i = 1; i <= up; ++i) { // 填i
            res = (res + dfs(p + 1, aho.next[u][i], is_limit && i == up, true)) % mod;
        }
    }
    else {
        for (int i = 0; i <= up; ++i) {
            res = (res + dfs(p + 1, aho.next[u][i], is_limit && i == up, true)) % mod;
        }
    }
    if (!is_limit && is_num) dp[p][u] = res;
    return res;
}

void solve() {
    cin >> N >> m;
    string s; 
    for (int i = 0; i < m; ++i) {
        cin >> s; // 可能有前导零
        aho.add_pattern(s);
    }
    aho.compute();
    // 数位dp
    memset(dp, -1, sizeof(dp));
    cout << dfs(0, 0, true, false) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}

