using ull = unsigned long long;
using ll = long long;

template<typename T, uint32_t MAX_BIT = 32>
struct Trie {
    static const int B = MAX_BIT;
    struct node {
        node* nxt[2];
        int sz;
        node() {
            nxt[0] = nxt[1] = NULL;
            sz = 0;
        }
    }* root;
    Trie() { root = new node(); }
    void insert(T val) {
        node* cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; i--) {
            int b = val >> i & 1;
            if (cur->nxt[b] == NULL)
                cur->nxt[b] = new node();
            cur = cur->nxt[b];
            cur->sz++;
        }
    }
    void del(T val) {
        node* cur = root;
        cur->sz--; // root 不会被删除
        for (int i = B - 1; i >= 0; --i) {
            int b = val >> i & 1;
            if (cur->nxt[b]->sz == 1) {
                // del(cur->nxt[b]);
                cur->nxt[b] = NULL;
                return;
            }
            cur = cur->nxt[b];
            cur->sz--;
        }
    }
    int query(T x, T k) { // number of values s.t. val ^ x < k
        node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            if (cur == NULL)
                break;
            int b1 = x >> i & 1, b2 = k >> i & 1;
            if (b2 == 1) {
                if (cur->nxt[b1])
                    ans += cur->nxt[b1]->sz;
                cur = cur->nxt[!b1];
            } else
                cur = cur->nxt[b1];
        }
        return ans;
    }
    T get_max(T x) { // returns maximum of val ^ x
        node* cur = root;
        T ans = 0;
        if (!cur->nxt[0] && !cur->nxt[1])
            return ans;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[!k])
                cur = cur->nxt[!k], ans <<= 1, ans++;
            else
                cur = cur->nxt[k], ans <<= 1;
        }
        return ans;
    }
    T get_min(T x) { // returns minimum of val ^ x
        node* cur = root;
        T ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[k])
                cur = cur->nxt[k], ans <<= 1;
            else
                cur = cur->nxt[!k], ans <<= 1, ans++;
        }
        return ans;
    }
    void del(node* cur) { // 删除所有的位
        for (int i = 0; i < 2; i++)
            if (cur->nxt[i])
                del(cur->nxt[i]);
        delete (cur);
    }
};
class Solution {
public:
    long long maxXor(int n, vector<vector<int>>& edges, vector<int>& values) {
        vector<int> g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        Trie<ull, 48> t;
        vector<ull> sum(n);

        int cnt = 0;

        function<void(int, int)> init = [&](int u, int fa) {
            sum[u] += values[u];
            for (int& v : g[u]) {
                if (v != fa) {
                    init(v, u);
                    sum[u] += sum[v];
                }
            }
            t.insert(sum[u]);
        };
        init(0, 0);

        ull ans = 0;
        function<void(int, int)> dfs = [&](int u, int fa) {
            t.del(sum[u]);
            for (int& v : g[u]) {
                if (v != fa) {
                    dfs(v, u);
                }
            }
            ans = max(ans, t.get_max(sum[u]));
        };
        dfs(0, 0);
        return ans;
    }
};