#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

struct DisjointSet {
  std::vector<int> father, rank;
  DisjointSet(int n): father(n), rank(n) {for(int i=0;i<n;i++) father[i]=i;}
  // 路径压缩
  int find(int v){return father[v]=father[v]==v?v:find(father[v]);}
  // 按秩合并
  void merge(int x,int y) {
    int a=find(x), b=find(y);
    if(rank[a]<rank[b]) father[a]=b;
    else {
      father[b]=a;
      if(rank[b]==rank[a]) ++rank[a];
    }
  }
};

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        DisjointSet dsu(n);
        ll sum = accumulate(nums.begin(), nums.end(), 0LL);
        for (auto sw : swaps) {
            dsu.merge(sw[0], sw[1]);
        }
        vector g(n, vector<int>{});
        for (int i = 0; i < n; ++i) {
            g[dsu.find(i)].push_back(i);
        }
        ll res = 0;
        for (int i = 0; i < n; ++i) {
            int m = 0;
            for (int v : g[i]) {
                if (v % 2 == 0) ++m;
            }
            ranges::sort(g[i], [&](const int x, const int y) { return nums[x] > nums[y]; });
            for (int j = 0; j < m; ++j) res += nums[g[i][j]];
        }
        return res * 2 - sum;
    }
};