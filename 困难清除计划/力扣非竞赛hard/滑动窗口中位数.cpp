class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        // 对顶的思想

        multiset<int> a, b;
        vector<double> ans; 
        int n = nums.size();

        // init
        for (int i = 0; i < n; ++i) {
            // 添加到 a 中
            if (a.size() + b.size() == k) {
                // 删除
                if (a.find(nums[i - k]) != a.end()) a.erase(a.find(nums[i - k])), a.insert(nums[i]);
                else b.erase(b.find(nums[i - k])), b.insert(nums[i]);
            }
            else {
                if (a.size() < k / 2) a.insert(nums[i]);
                else b.insert(nums[i]);
            }
            // 大小调整
            while (!a.empty() && !b.empty() && *b.begin() < *a.rbegin()) {
                int u = *b.begin(), v = *a.rbegin();
                b.erase(b.begin());
                a.erase(prev(a.end()));
                a.insert(u);
                b.insert(v);
            }
            if (i < k - 1) continue;
            if (k & 1) ans.push_back((double)(*b.begin()));
            else ans.push_back(((double)*a.rbegin() + *b.begin()) / 2);
        }
        return ans;
    }
};