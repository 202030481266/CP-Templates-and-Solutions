#include <bits/stdc++.h>
using namespace std;

int cnt[100005];
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        // 二分答案+滑动窗口
        int n = nums.size(); 
        long long tot = 1ll * (n + 1) * n / 2; // 10^5*10^5/2=5*10^9>INT_MAX
        set<int> s;
        for (auto& v : nums) s.insert(v);
        int k = s.size(); // 种类个数

        auto check = [&](int val) -> bool {
            int type = 0;
            memset(cnt, 0, sizeof(cnt));
            int l = 0; 
            long long res = 0;
            for (int i = 0; i < n; ++i) {
                ++cnt[nums[i]];
                if (cnt[nums[i]] == 1) ++type;
                while (type > val) {
                    --cnt[nums[l]];
                    if (cnt[nums[l]] == 0) --type;
                    ++l;
                }
                res += (i - l + 1);
            }
            return res >= (tot-1)/2+1;
        };

        // 找到最小的种类数mid,其中窗口里面的数字的种类不超过mid,然后所有符合这种条件的子数组个数>=tot/2
        int l = 0, r = k; //(l,r]
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }
};
