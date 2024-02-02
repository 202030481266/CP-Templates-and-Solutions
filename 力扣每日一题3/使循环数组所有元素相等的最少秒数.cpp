class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        unordered_map<int, int> idx;
        int id = 0;
        for (int& v : nums) {
            if (!idx.count(v)) {
                idx[v] = id++;
            }
        }
        vector<int> arr[id];
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            arr[idx[nums[i]]].push_back(i);
        }
        int ans = INT_MAX, res;
        for (int i = 0; i < id; ++i) {
            res = n - 1 - (arr[i].back() - arr[i][0]);
            for (int j = 0; j + 1 < arr[i].size(); ++j) {
                res = max(res, arr[i][j + 1] - arr[i][j] - 1);
            }
            ans = min(ans, (res + 1) / 2);
        }
        return ans;
    }
};