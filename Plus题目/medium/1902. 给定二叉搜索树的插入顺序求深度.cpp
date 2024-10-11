#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// BST 扁平化思考即可

class Solution {
public:
    int maxDepthBST(vector<int>& order) {
        int n = order.size();
        set<pii> s;
        s.insert({inf, 0});
        s.insert({-inf, 0});
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            auto it = s.lower_bound({order[i],-1});
            int res = 0;
            if (it != s.begin()) res = max(res, prev(it)->second);
            if (it != s.end()) res = max(res, it->second);
            ans = max(ans, res + 1);
            s.insert({order[i], res+1});
        }
        return ans;
    }
};