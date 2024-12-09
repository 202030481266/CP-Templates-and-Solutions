#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 贪心做法是一个非常困难的实现

class Solution {
public:
    int minArraySum(vector<int>& a, int k, int op1, int op2) {
        vector<int> nums;
        for (int v : a) {
            if (v) nums.push_back(v);
        }
        if (nums.empty()) return 0;
        sort(nums.begin(), nums.end());
        int n = nums.size(), p = n - 1;

        while (p >= 0 && nums[p] >= 2*k-1 && op1) {
            nums[p] = (nums[p]+1)/2;
            --p;
            --op1;
        }
        // (p,n-1] >= 2*k-1
        for (int i = n-1; i > p && op2; --i) {
            nums[i] -= k;
            --op2;
        }
        int ans = 0;
        for (int i = n-1; i > p; --i) ans += nums[i];
        int q = 0;
        while (q <= p && nums[q] < k) q++; // [0,q) is < k and [q,p] is [k,2*k-1)
        // [q, p]
        int odd = 0, pt = q, m = p-min(op1,p-q+1)+1; 

        unordered_map<int,int> mp;
        for (; pt <= p && op2; --op2, ++pt) {
            nums[pt] -= k;
            if (pt >= m && nums[pt] % 2 && k % 2) {
                mp[nums[pt]]++;
            }
        }
        for (int i = max(m,pt); i <= p; ++i) {
            if (nums[i] & 1) ++odd;
        }
        sort(nums.begin(),nums.begin()+p+1);
        if (k & 1) {
            // 重新调整
            for (int i = max(0,p-op1+1); i <= p && odd; ++i) {
                if (mp[nums[i]] > 0) {
                    mp[nums[i]]--;
                    odd--;
                    ans--;
                }
            }
        }
        for (int i = p; i >= 0; --i) {
            if (op1) {
                nums[i] = (nums[i]+1)/2;
                --op1;
            }
            ans += nums[i];
        }
        return ans;
    }
};