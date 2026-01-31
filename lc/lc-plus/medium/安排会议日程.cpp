#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(slots1.begin(), slots1.end());
        sort(slots2.begin(), slots2.end());
        int n = slots1.size(), m = slots2.size();
        int p = 0, q = 0;
        while (p < n && q < m) {
            // 保证区间出现交集
            while (p < n && slots1[p][1] < slots2[q][0]) p++;
            while (q < m && slots2[q][1] < slots1[p][0]) q++;
            if (p == n || q == m) break;
            int l = max(slots1[p][0], slots2[q][0]), r = min(slots1[p][1], slots2[q][1]);
            if (l + duration <= r) return {l, l + duration};    
            if (slots1[p][1] < slots2[q][1]) p++;
            else if (slots1[p][1] > slots2[q][1]) q++;
            else p++, q++;
        }
        return {};
    }
};
