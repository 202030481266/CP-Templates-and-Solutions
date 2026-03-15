#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> par, rnk, sz;
    int c;
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n)
    {
        for (int i = 1; i <= n; ++i)
            par[i] = i;
    }
    int find(int i)
    {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(int i, int j)
    {
        return find(i) == find(j);
    }
    int get_size(int i)
    {
        return sz[find(i)];
    }
    int count()
    {
        return c; // connected components
    }
    int merge(int i, int j)
    {
        if ((i = find(i)) == (j = find(j)))
            return -1;
        else
            --c;
        if (rnk[i] > rnk[j])
            swap(i, j);
        par[i] = j;
        sz[j] += sz[i];
        if (rnk[i] == rnk[j])
            rnk[j]++;
        return j;
    }
};

struct node {
    int x, y, id;
    node(int _x, int _y, int _id): x(_x), y(_y), id(_id) {}
};

class Solution {
public:
    int maxActivated(vector<vector<int>>& points) {
        int n = points.size();
        DSU dsu(n);
        vector<node> arr;
        for (int i = 0; i < n; ++i) {
            arr.push_back(node(points[i][0], points[i][1], i));
        }
        ranges::sort(arr, [&](const node& a, const node& b){ return a.x < b.x; });
        int p = 0;
        while (p < n) {
            int i = p + 1;
            while (i < n && arr[i].x == arr[p].x) ++i;
            for (int j = p + 1; j < i; ++j) {
                dsu.merge(arr[j].id, arr[j - 1].id);
            }
            p = i;
        }
        ranges::sort(arr, [&](const node& a, const node& b){ return a.y < b.y; });
        p = 0;
        while (p < n) {
            int i = p + 1;
            while (i < n && arr[i].y == arr[p].y) ++i;
            for (int j = p + 1; j < i; ++j) {
                dsu.merge(arr[j].id, arr[j - 1].id);
            }
            p = i;
        }
        int mx1 = 0, mx2 = 0;
        for (int i = 0; i < n; ++i) {
            if (dsu.find(i) != i) continue;
            int sz = dsu.get_size(i);
            if (sz > mx1) {
                mx2 = mx1;
                mx1 = sz;
            }
            else if (sz > mx2) mx2 = sz;
        }
        return mx1 + mx2 + 1;
    }
};