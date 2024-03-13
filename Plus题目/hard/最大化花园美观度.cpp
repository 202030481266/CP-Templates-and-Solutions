class Solution {
public:
    int maximumBeauty(vector<int>& nums) {
        int n = nums.size(), sum[n + 1];
        memset(sum, 0, sizeof(sum));

        for (int i = 0; i < n; ++i)
            sum[i + 1] = sum[i] + max(0, nums[i]);

        map<int, int> mp;
        vector<vector<int>> arr;
        int tot = 0;
        for (int i = 0; i < n; ++i) {
            if (!mp.count(nums[i])) {
                mp[nums[i]] = tot++;
                arr.push_back({i + 1});
            }
            else {
                arr[mp[nums[i]]].push_back(i + 1);
            }
        }
        int ans = INT_MIN;
        for (vector<int>& v : arr) {
            int mn = sum[v[0] - 1], tmp = INT_MIN, x = (nums[v[0] - 1] < 0 ? 2 * nums[v[0] - 1] : 0);
            for (int i = 1; i < v.size(); ++i) { // [v[i], v[i + 1]]
                tmp = max(tmp, sum[v[i]] - mn + x);
                mn = min(mn, sum[v[i] - 1]);
            }
            ans = max(ans, tmp);
        }
        return ans;
    }
};