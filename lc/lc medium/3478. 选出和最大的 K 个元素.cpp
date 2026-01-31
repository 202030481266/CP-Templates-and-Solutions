#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return nums1[a] < nums1[b];
        });
        vector<ll> ans(n);
        int p = 0;
        ll sum = 0;
        priority_queue<int, vector<int>, greater<int>> q;
        while (p < n) {
            int i = p+1;
            while (i < n && nums1[ids[i]] == nums1[ids[p]]) ++i;
            for (int j = p; j < i; ++j) {
                ans[ids[j]] = sum;
            }
            for (int j = p; j < i; ++j) {
                q.push(nums2[ids[j]]);
                sum += nums2[ids[j]];
                if (q.size() > k) {
                    sum -= q.top();
                    q.pop();
                }
            }
            p = i;
        }
        return ans;
    }
};