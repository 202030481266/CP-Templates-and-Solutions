#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int secondsToRemoveOccurrences(string s) {
        int n = s.size();
        vector<int> pos;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '1') pos.push_back(i);
        }
        int m = pos.size(), ans = 0;
        for (int i = 0; i < m; ++i)
        {
            if (pos[i] != i)
                ans = max(ans, pos[i] - i + (m - 1 - i));
        }
        return ans;
    }
};