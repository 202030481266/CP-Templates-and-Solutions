class Solution {
    using ll = long long;
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        // 问题就是求解所有的区间[i, i + dist) 的前 k-1 个值的和
        // 需要使用两个有序集合来完成
        multiset<int> s1;
        multiset<int> s2;
        ll ans = 1e15, sum = 0;

        int n = nums.size(), l = 1;

        for (int i = 1; i < n; ++i) {
            // 先删除, 后插入
            while (l < i - dist) {
                if (s2.find(nums[l]) != s2.end()) {
                    s2.erase(s2.find(nums[l++]));
                }
                else {
                    s1.erase(s1.find(nums[l]));
                    sum -= nums[l++];
                    while (s1.size() < k - 1 && !s2.empty()) {
                        // move the smallest element to s1
                        s1.insert(*s2.begin());
                        sum += *s2.begin();
                        s2.erase(s2.begin());
                    }
                }
            }
            // insert
            if (s1.size() < k - 1) {
                s1.insert(nums[i]);
                sum += nums[i];
            }
            else {
                s2.insert(nums[i]);
                while (*s1.rbegin() > *s2.begin()) {
                    int u = *s1.rbegin(), v = *s2.begin();
                    s1.erase(prev(s1.end()));
                    s2.erase(s2.begin());
                    s2.insert(u);
                    s1.insert(v);
                    sum += (v - u);
                }
            }
            if (s1.size() == k - 1) {
                ans = min(ans, sum + nums[0]);
            }
        }
        return ans;
    }
};