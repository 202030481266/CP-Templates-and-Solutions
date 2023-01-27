class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) 
            a[i] = a[i - 1] + (nums[i - 1] >= k);
        unordered_map<int,int> hs;
        int pos = -1;
        for (int i = 1; i <= n; i++) 
            if (nums[i - 1] == k) {
                pos = i;
                break;
            }
        for (int i = pos; i <= n; i++) 
            ++hs[2 * a[i] - i];
        int ans = 0;
        for (int i = 1; i <= pos; i++) {
            ans += hs[2 * a[i - 1] - i + 3];
            ans += hs[2 * a[i - 1] - i + 2];
        }
        return ans;
    }
};