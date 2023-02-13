class BIT {
private:
    vector<int> tree;
    int n;

public:
    BIT(int _n) : n(_n), tree(_n + 1) {}
    static constexpr int lowbit(int x) {
        return x & (-x);
    }
    void update(int x, int d) {
        while (x <= n) {
            tree[x] += d;
            x += lowbit(x);
        }
    }
    int query(int x) const {
        int ans = 0;
        while (x) {
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
};
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        vector<int> a(nums.begin(), nums.end());
        vector<int> b(nums.begin(), nums.end());
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());

        for (auto& c : a) 
            c = lower_bound(nums.begin(), nums.end(), c) - nums.begin() + 1;
        
        int n = a.size();
        BIT tree(n);
        tree.update(a[0], 1);

        long long ans = 0;
        for (int i = 1; i < n; ++i) {
            int l = lower_bound(nums.begin(), nums.end(), lower - b[i]) - nums.begin() + 1;
            int r = lower_bound(nums.begin(), nums.end(), upper - b[i]) - nums.begin() + 1;
            if (r == nums.size() + 1) --r;
            if (nums[r - 1] > upper - b[i]) --r;
            if (r >= l)
                ans += (tree.query(r) - tree.query(l - 1));
            tree.update(a[i], 1);
        }
        return ans;
    }
};
