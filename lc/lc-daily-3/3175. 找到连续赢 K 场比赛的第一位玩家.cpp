#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int mx_p = max_element(skills.begin(), skills.end()) - skills.begin();
        int n = skills.size();
        stack<int> s;
        vector<int> right(n);
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && skills[s.top()] < skills[i]) {
                right[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        int mx = 0;
        for (int i = 0; i < mx_p; ++i) {
            int res = right[i] - i - 1;
            if (mx && skills[i] > mx) ++res;
            if (res >= k) return i;
            mx = max(mx, skills[i]);
        }
        return mx_p;
    }
};