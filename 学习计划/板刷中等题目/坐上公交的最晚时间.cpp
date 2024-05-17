#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 比较复杂的模拟题目
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());    
        sort(passengers.begin(), passengers.end());
        // 找到最大的时刻 t， 满足 max(0, pre - x * cap) + 1 <= (n - x) * cap
        int n = buses.size(), m = passengers.size();
        // (0,b0] 表示有 0 辆车走了，剩下 n 辆车
        // (b0,b1] 表示 1 辆车走了，剩下 n-1 辆车
        // .... (bn-2, bn-1] 表示 n-1 辆车走了，剩下 1 辆车
        vector<int> mex(m);
        mex[0] = passengers[0] - 1;
        for (int i = 1; i < m; ++i) {
            if (passengers[i] - 1 == passengers[i-1]) mex[i] = mex[i-1];
            else mex[i] = passengers[i]-1;
        }
        int pre = 0, ans = 0, gone = 0;
        for (int i = 0; i < n; ++i) {
            // 有 i 辆车走了，剩下 n-i 辆车, [pre, gone] 仍然没有走的乘客
            while (pre < m && passengers[pre] <= buses[i] && pre - gone + 2 <= 1ll * (n - i) * capacity) ++pre;
            // [0, pre) 表示乘客区间都是可以的
            if (pre == m) {
                // 只要在最后一辆车之前走就可以了
                if (passengers[m-1] == buses[n-1]) ans = mex[m-1];
                else ans = buses[n-1];
                break;
            }
            else {
                // 赶在最后一辆车走就行了
                int tmp = min(buses[n-1], mex[pre]); 
                // 这个时间点可能是 passengers[pre-1] 的到达时间
                if (pre - 1 >= 0 && tmp == passengers[pre-1]) ans = mex[pre-1];
                else ans = tmp;
            }
            // update the gone
            int c = capacity;
            while (gone < pre && c && passengers[gone] <= buses[i]) ++gone, --c;  // 这一个阶段
        }
        return ans;
    }
};
