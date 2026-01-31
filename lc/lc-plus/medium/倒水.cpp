#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        int n = heights.size();
        // 一个直观的方法就是模拟,直接构造似乎非常复杂
        // 除了模拟目前没有更好的方法，因为不属于统计问题，而是构造具体方案
        while (volume--) {
            int i = k;
            while (i > 0 && heights[i] >= heights[i - 1]) --i;
            while (i < k && heights[i] == heights[i + 1]) ++i;
            if (i < k) {
                ++heights[i];
                continue;
            }
            while (i < n - 1 && heights[i] >= heights[i + 1]) ++i;
            while (i > k && heights[i] == heights[i - 1]) --i;
            if (i > k) {
                ++heights[i];
                continue;
            }
            ++heights[k];
        }
        return heights;
    }
};
