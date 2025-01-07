// #include "mystl.h"
// #include "debug.h"
// #include "Math.h"
// using namespace std;


class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1) {
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
    int chaseGame(vector<vector<int>>& edges, int startA, int startB) {
        int n = edges.size();

        // from index 1 to n
        vector<vector<int>> g(n + 1);
        vector<int> du(n + 1);
        vector<int> on_circle(n + 1);

        for (auto& e : edges) {
            int x = e[0], y = e[1];
            if (x == startA && y == startB || x == startB && y == startA) return 1;
            g[x].push_back(y);
            g[y].push_back(x);
            ++du[x];
            ++du[y];
        }

        UnionFind un(n + 1);

        // topu sort
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (du[i] == 1) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int& v : g[u]) {
                --du[v];
                un.unite(u, v);
                if (du[v] == 1) q.push(v);
            }
        }

        int fatherB = 0, fatherA = 0, len = 0;
        for (int i = 1; i <= n; ++i) {
            if (du[i] > 1) {
                ++len;
                on_circle[i] = 1;
                if (un.find(i) == un.find(startA)) fatherA = i;
                if (un.find(i) == un.find(startB)) fatherB = i;
            }
        }

        assert(fatherB != 0);
        assert(fatherA != 0);

        cout << fatherA << ' ' << fatherB << endl;

        int path = 0, x = fatherA;
        while (x != fatherB) {
            ++path;
            du[x] = 1;
            for (int& v : g[x]) {
                if (du[v] > 1) {
                    x = v;
                    break;
                }
            }
        }
        path = min(path, len - path); // get the minimum value of circle path from fatherA -> fatherB

        vector<int> dis(n + 1), mx(n + 1), father(n + 1);
        function<void(int, int)> cal = [&](int u, int fa) {
            for (int& v : g[u]) {
                if (v != fa && !on_circle[v]) {
                    dis[v] = dis[u] + 1;
                    mx[v] = dis[v];
                    father[v] = u;
                    cal(v, u);
                    mx[u] = max(mx[u], mx[v]);
                }
            }
        };
        for (int i = 1; i <= n; ++i) {
            if (on_circle[i]) {
                cal(i, 0);
            }
        }
        int dA = dis[startA], dB = dis[startB];
        cout << dA << ' ' << dB << endl; 
        // when the circle is 3, it is complex
        if (dA + path - 1 > dB) {
            // B can be arrive at cirle early
            // but the circle is 3,it is never can be roop
            // at this time, the problem is super complex
            if (len > 3) return -1;
            vector<int> a;
            for (int i = 1; i <= n; ++i) {
                if (on_circle[i]) {
                    a.push_back(i);
                }
            }
            assert(a.size() == 3);
            // find the distance from startB -> fatherA
            int ans = 0, tmp = 0, ff = startA;
            while (father[ff] != fatherA) ff = father[ff];
            for (int& v : g[fatherA]) {
                if (v != ff) tmp = max(tmp, mx[v]);
            }
            if (fatherB == fatherA) {
                for (int i = 0; i < 3; ++i) {
                    if (a[i] == fatherA) ans = max(ans, dA + tmp);
                    else ans = max(ans, dA + mx[a[i]] + 1);
                }
            }
            else {
                for (int i = 0; i < 3; ++i) {
                    if (a[i] == fatherB) ans = max(ans, dA + 1 + mx[fatherB]);
                    else if (a[i] == fatherA) {
                        if (dB + 1 < dA - 1) ans = max(ans, dA + tmp);
                    }
                    else {
                        if (dB + 1 < dA) ans = max(ans, dA + 1 + mx[a[i]]);
                    }
                }
            }
            return ans;
        }
        // A can be arrive early
        // fatherA == fatherB
        // need to get the lca
        int mx_val = 0, cost = 0, distance = (dA + path + dB - 2) / 2, anc = 0;
        if (fatherA == fatherB) {
            int x = startA, y = startB;
            while (x != y) {
                if (dis[x] > dis[y]) x = father[x];
                else if (dis[x] < dis[y]) y = father[y];
                else x = father[x], y = father[y];
            }
            anc = x;
            distance = (dis[startA] + dis[startB] - 2 * dis[anc] - 2) / 2;
        }
        else {
            distance = (dA + path + dB - 2) / 2;
        }
        // all right, seems two of them can be stick around, otherwise it is super complex 
        // we need find the longest path in fatherB
        x = startB; 
        while (cost <= distance) {
            mx_val = max(mx[x], mx_val);
            ++cost;
            x = father[x];
        }
        if (fatherA == fatherB) {
            return dis[startA] + mx_val - 2 * dis[anc];
        }
        else return dA + path + mx_val;
    }

};



