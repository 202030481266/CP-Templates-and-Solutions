#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
public:
    UnionFind(int size) : parent(size, -1), rank(size, 0) {}
    int find(int x) {
        if (parent[x] == -1) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        if (xRoot == yRoot) return false;
        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[yRoot] < rank[xRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
        return true;
    }
    bool isSame(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& a, vector<string>& b, vector<vector<string>>& c) {
        int n = a.size(), m = b.size(), tot=0;
        if (n != m) return false;
        unordered_map<string,int> mp;
        for (string& s:a) {
            if (!mp.count(s)) mp[s]=tot++;
        }
        for (string& s:b) {
            if (!mp.count(s)) mp[s]=tot++;
        }
        for (auto& s:c) {
            if (!mp.count(s[0])) mp[s[0]]=tot++;
            if (!mp.count(s[1])) mp[s[1]]=tot++;
        }
        UnionFind un(tot);
        for (auto& ws : c) {
            un.unite(mp[ws[0]], mp[ws[1]]);
        }
        for (int i = 0; i < n; ++i) {
            if (!un.isSame(mp[a[i]],mp[b[i]])) return false;
        }
        return true;
    }
};