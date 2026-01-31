#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, int> st;
        unordered_map<string, bool> vis;
        for (string& s : strings) 
            st[s]++;
        vector<vector<string>> ans;
        for (string& s : strings) {
            if (vis[s]) continue;
            vis[s] = true;
            vector<string> res;
            for (int i = 0; i < 26; ++i) {
                string t = s;
                for (char& c : t) {
                    c = (c - 'a' + i) % 26 + 'a';
                }
                if (st.count(t)) {
                    vis[t] = true;
                    for (int k = 0; k < st[t]; ++k) // 这里需要多次放入答案中
                        res.push_back(t);
                }
            }
            ans.push_back(res);
        }
        return ans;
    }
};