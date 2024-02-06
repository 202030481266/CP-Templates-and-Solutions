// O(n ^ 2)
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();

        int dp[n][2];
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < n; ++i) {
            dp[i][0] = dp[i][1] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i][1] = max(dp[i][1], dp[j][0] + 1);
                }
                else if (nums[j] > nums[i]) {
                    dp[i][0] = max(dp[i][0], dp[j][1] + 1);
                }
            }
        }

        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};

// O(n)
// greedy algorithm
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0, flag, last = nums[0];

        int p = 0;
        while (p < n && nums[p] == nums[0]) ++p;
        if (p == n) return 1;
        if (nums[p] > nums[0]) flag = 1;
        else flag = 0;
        ++ans;

        while (p < n) {
            if (flag) {
                if (nums[p - 1] > nums[p]) {
                    if (nums[p - 1] != last) ++ans;
                    last = nums[p - 1];
                    flag = 0;
                }
            } 
            else {
                if (nums[p - 1] < nums[p]) {
                    if (nums[p - 1] != last) ++ans;
                    last = nums[p - 1];
                    flag = 1;
                }
            }
            ++p;
        }
        if (flag && nums[n - 1] > last) ++ans;
        if (!flag && nums[n - 1] < last) ++ans;  
        return ans;
    }
};