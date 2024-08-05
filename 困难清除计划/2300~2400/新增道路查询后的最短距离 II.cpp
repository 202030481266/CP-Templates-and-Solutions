#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // 很复杂的一道题目
        // 本质就是区间合并和扩展，但是难点在于很难维护
        set<int> s;
        for (int i = 0; i < n; ++i) {
            s.insert(i);
        }
        vector<int> ans;
        for (auto& q : queries) {
            // 首先判断这个是否在某一个区间里面
            auto it = s.lower_bound(q[0]);
            if (*it == q[0] && next(it) != s.end() && *next(it) < q[1]) { // 一开始的时候就决定了
                it = next(it);
                while (it != s.end() && *it < q[1]) 
                    it = s.erase(it);
                s.insert(q[1]);
            }
            ans.push_back(s.size()-1);
        }
        return ans;
    }
};