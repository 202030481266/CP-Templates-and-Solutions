class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        int n = words.size(), status[n];
        memset(status, 0, sizeof(status));
        UnionFind un(n);
        unordered_map<int, int> exi;
        for (int i = 0; i < n; ++i) {
            int& tmp = status[i];
            for (char& ch : words[i]) 
                tmp |= (1 << (ch - 'a'));
            if (exi.count(tmp)) un.unite(exi[tmp], i);
            exi[tmp] = i;
        }
        for (int i = 0; i < n; ++i) {
            int& tmp = status[i];
            for (int j = 0; j < 26; ++j) {
                if ((tmp >> j) & 1) {
                    // add
                    int res = (tmp ^ (1 << j));
                    if (exi.count(res) && !un.connected(exi[res], i)) {
                        un.unite(exi[res], i);
                        break;
                    }
                    // subtitue
                    for (int k = 0; k < 26; ++k) {
                        if (exi.count(res | (1 << k)) && !un.connected(exi[res | (1 << k)], i)) {
                            un.unite(exi[res | (1 << k)], i);
                            break;
                        }
                    }
                }
                else {
                    // delete
                    if (exi.count(tmp | (1 << j)) && !un.connected(exi[tmp | (1 << j)], i)) {
                        un.unite(exi[tmp | (1 << j)], i);
                        break;
                    }
                }
            }
        }
        int siz[n], cnt = 0, ans = 0;
        memset(siz, 0, sizeof(siz));
        for (int i = 0; i < n; ++i) {
            ++siz[un.find(i)];
        }
        for (int i = 0; i < n; ++i)
            if (siz[i] > 0) {
                ++cnt;
                ans = max(ans, siz[i]);
            }
        return {cnt, ans};
    }
};


// 上面的代码虽然复杂度和下面的相同，但是下面的可以过，上面的会被卡常数（是因为标准库的问题）
// 原因在于并查集的合并次数很多，而且每一次都是调用unordered_map就很慢，但是使用数组建图显然快很多
// 并且还有一个关键原因在于bfs只会访问一次节点，实际上并查集也完全可以这样做，但是我懒得写

class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        // 使用哈希映射统计每一个二进制表示出现的次数
        unordered_map<int, int> wordmasks;
        for (const string& word: words) {
            int mask = 0;
            for (char ch: word) {
                mask |= (1 << (ch - 'a'));
            }
            ++wordmasks[mask];
        }
        
        // 辅助函数，用来得到 mask 的所有可能的相邻节点
        auto get_adjacent = [](int mask) -> vector<int> {
            vector<int> adj;
            // 将一个 0 变成 1，或将一个 1 变成 0
            for (int i = 0; i < 26; ++i) {
                adj.push_back(mask ^ (1 << i));
            }
            // 将一个 0 变成 1，且将一个 1 变成 0
            for (int i = 0; i < 26; ++i) {
                if (mask & (1 << i)) {
                    for (int j = 0; j < 26; ++j) {
                        if (!(mask & (1 << j))) {
                            adj.push_back(mask ^ (1 << i) ^ (1 << j));
                        }
                    }
                }
            }
            return adj;
        };
        
        unordered_set<int> used;
        int best = 0, cnt = 0;
        for (const auto& [mask, occ]: wordmasks) {
            if (used.count(mask)) {
                continue;
            }
            // 从一个未搜索过的节点开始进行广度优先搜索，并求出对应连通分量的大小
            queue<int> q;
            q.push(mask);
            used.insert(mask);
            // total 记录联通分量的大小
            int total = occ;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v: get_adjacent(u)) {
                    if (wordmasks.count(v) && !used.count(v)) {
                        q.push(v);
                        used.insert(v);
                        total += wordmasks[v];
                    }
                }
            }
            best = max(best, total);
            ++cnt;
        }
            
        return {cnt, best};
    }
};

