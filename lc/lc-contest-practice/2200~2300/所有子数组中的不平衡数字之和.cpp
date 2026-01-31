class Solution {
    int a[1001];
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        int n = nums.size();
        // 考虑贡献 一个数字能够对多少区间产生贡献
        vector<int> right(n, n);
        fill(a, a + n + 1, n);
        for (int i = n - 1; i >= 0; --i) {
            right[i] = min(a[nums[i]], a[nums[i] - 1]);
            a[nums[i]] = i;
        }
        int ans = 0;
        memset(a, -1, sizeof(a));
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            ans += (i - a[x - 1]) * (right[i] - i);
            a[x] = i;
        }
        return ans - n * (n + 1) / 2;
    }
};



class Solution {
    int a[1010];
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; ++i) {
            memset(a, 0, sizeof(a));
            int cnt = 0;
            a[nums[i]] = 1;
            for (int j = i + 1; j < n; ++j) {
                int x = nums[j];
                if (!a[x]) {
                    cnt += 1 - a[x - 1] - a[x + 1];
                    a[x] = 1;
                }
                ans += cnt;
            }
        }
        return ans;
    }
};