typedef pair<int, int> pii;
struct Trie {
    Trie* left = nullptr;
    Trie* right = nullptr;
    int num = 0;
    Trie() {}
};
class Solution {
    static constexpr int H = 18;
    Trie* root = new Trie();
    int n;
    vector<vector<int>> g;
    vector<vector<pii>> q;
    vector<int> ans;
public:
    void add(int x) {
        Trie* cur = root;
        for (int i = H; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (!bit) {
                if (!cur->left) cur->left = new Trie();
                cur = cur->left;
            }
            else {
                if (!cur->right) cur->right = new Trie();
                cur = cur->right;
            }
            ++cur->num;
        }
    }
    void del(int x) {
        Trie* cur = root;
        for (int i = H; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (!bit) {
                cur->left->num -= 1;
                if (cur->left->num == 0) {
                    cur->left = nullptr;
                    break;
                }
                cur = cur->left;
            }
            else {
                cur->right->num -= 1;
                if (cur->right->num == 0) {
                    cur->right = nullptr;
                    break;
                }
                cur = cur->right;
            }
        }
        
    }
    int get(int m) {
        Trie* cur = root;
        int x = 0;
        for (int i = H; i >= 0; --i) {
            int bit = (m >> i) & 1;
            if (!bit) {
                if (cur->right) {
                    cur = cur->right;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->left;
                    x *= 2;
                }
            }
            else {
                if (cur->left) {
                    cur = cur->left;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->right;
                    x *= 2;
                }
            }
        }
        return x;
    }
    void dfs(int u) {
        add(u);
        for (auto& c : q[u]) {
            ans[c.second] = get(c.first);
        }
        for (int& v : g[u]) {
            dfs(v);
        }
        del(u);
    }
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        // log2(100000)=16.6
        n = parents.size();
        int rt = 0;
        g = vector(n, vector<int>());
        q = vector(n, vector<pii>());
        for (int i = 0; i < n; ++i) {
            if (parents[i] >= 0) {
                g[parents[i]].push_back(i);
            }
            else rt = i;
        }
        int N = queries.size();
        ans = vector<int>(N);
        for (int i = 0; i < N; ++i) {
            auto& c = queries[i];
            q[c[0]].emplace_back(c[1], i);
        }
        dfs(rt);
        return ans;
    }
};