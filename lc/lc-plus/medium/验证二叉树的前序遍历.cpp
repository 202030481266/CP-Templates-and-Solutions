#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> s;
        int pre;
        s.push(0);
        for (int& v : preorder) {
            while (!s.empty() && s.top() < v) {
                pre = s.top();
                s.pop();
            }
            if (v < pre) return false;
            s.push(v);
        }
        return true;
    }
};