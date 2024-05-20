#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> arr;
        for (int i = 0; i < n; ++i) {
            int j = n - 1;
            while (j >= 0 && grid[i][j] == 0) --j;
            arr.push_back(n - 1 - j); // (j, m-1]
        }
        // 交换操作使得 arr[i] >= n-1-i
        // 贪心，每一次都是最近的右边数字选取，可以简单证明这是最优解
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] < n-1-i) {
                int p = -1;
                for (int j = i+1;j < n; ++j) {
                    if (arr[j] >= n-1-i) {
                        p = j;
                        break;
                    }
                }
                if (p==-1) return -1;
                for (int j = p; j > i; --j) {
                    swap(arr[j], arr[j-1]);
                    ++ans;
                }   
            }
        }
        return ans;
    }
};