// xiaoshulin
// 2024.1.10

class Solution {
	using ll = long long;
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();

        int flag = true;
        for (int i = 1; i < n; ++i) {
            if (nums[i] <= nums[i - 1]) {
                flag = false;
                break;
            }
        }
        if (flag) return 1ll * n * (n + 1) / 2;

        vector<int> pre{0};
        for (int i = 0; i < n; ++i) {
            if (nums[i] > pre.back()) pre.push_back(nums[i]);
            else break;
        }
        vector<int> suf{nums.back()};
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < suf.back()) suf.push_back(nums[i]);
            else break;
        }
		suf.push_back(0);
		reverse(suf.begin(), suf.end());
		int x = pre.size() - 1, y = suf.size() - 1, N = suf.size() - 1;
		ll ans = 0;
		while (x >= 0) {
			while (y >= 0 && suf[y] > pre[x]) --y; // we can delete the interval [y, N - 1] all can delete
			ans += (N - y + 1);
			--x;
		}
		return ans;
    }
};
