// O(n)，经典后缀自动机算法
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

struct SuffixAutomaton
{
    struct node
    {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> t;
    vector<int> terminal;
    vector<long long> dp;
    vector<vector<int>> g;
    SuffixAutomaton() {}
    SuffixAutomaton(int n)
    {
        t.resize(2 * n);
        terminal.resize(2 * n, 0);
        dp.resize(2 * n, -1);
        sz = 1;
        last = 0;
        g.resize(2 * n);
        t[0].len = 0;
        t[0].link = -1;
        t[0].firstpos = 0;
    }
    void extend(char c)
    {
        int p = last;
        if (t[p].nxt.count(c))
        {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1)
            {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q)
            {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c))
        {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1) t[cur].link = 0;
        else
        {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else
            {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q)
                {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
    void build_tree()
    {
        for (int i = 1; i < sz; i++) g[t[i].link].push_back(i);
    }
    void build(string &s)
    {
        for (auto x : s)
        {
            extend(x);
            terminal[last] = 1;
        }
        build_tree();
    }
    long long cnt(int i)   //number of times i-th node occurs in the string
    {
        if (dp[i] != -1) return dp[i];
        long long ret = terminal[i];
        for (auto &x : g[i]) ret += cnt(x);
        return dp[i] = ret;
    }
};


class Solution {
public:
    int countDistinct(string s) {
        SuffixAutomaton sa(s.size());
        sa.build(s);
        // 在后缀自动机上进行DAG统计或者直接使用endpos集合大小的定义
        int ans = 0;
        for (int i = 1; i < sa.sz; i++)
        {
            ans += sa.t[i].len - sa.t[sa.t[i].link].len;
        }
        return ans;
    }
};