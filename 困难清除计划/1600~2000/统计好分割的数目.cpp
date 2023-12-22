// xiaoshulin
// 2023.12.22
class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums) {
        int n = nums.size();
        const int mod = 1e9 + 7;

		unordered_map<int, int> last;
		for (int i = 0; i < n; ++i) {
			last[nums[i]] = i;
		}
		int cnt = -1, r = 0;
		for (int i = 0; i < n; ++i) {
			r = max(r, last[nums[i]]);
			if (i == r) {
				++cnt;
			}
		}
		// pow(2, cnt)
		long long ans = 1, base = 2;
		for (; cnt; cnt >>= 1) {
			if (cnt & 1) ans = ans * base % mod;
			base = base * base % mod;
		}
		return ans;
    }
};
