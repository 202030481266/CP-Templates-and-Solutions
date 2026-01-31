#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f; 
class Solution {
public:
    int minOperations(vector<int>& a, vector<int>& b) {
        int n = a.size();
        //两种情况
        // no swap the n - 1
        int ans = inf;
        auto cal = [&]() -> int { 
            int cur = 0, flag = 1;
            for (int i = 0; i < n - 1; ++i) {
                if (a[i] > a[n-1]) {
                    if (b[i] > a[n-1] || a[i] > b[n-1]) {
                        flag = 0;
                        break;
                    }
                    else {
                        ++cur;
                    }
                }
                if (b[i] > b[n-1]) {
                    if (b[i] > a[n-1] || a[i] > b[n-1]) {
                        flag = 0;
                        break;
                    }
                    else {
                        ++cur;
                    }
                }
            }
            return flag ? cur : inf;
        };
        ans = min(ans, cal());
        swap(a[n-1], b[n-1]);
        ans = min(ans, cal() + 1);
        return ans == inf ? -1 : ans;
    }
};
