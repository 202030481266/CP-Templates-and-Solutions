// https://leetcode.cn/problems/count-array-pairs-divisible-by-k/



// 奇迹，居然可以卡过去
class Solution {
	int cnt[100010];
public:
    long long countPairs(vector<int>& nums, int k) {
    	// 0 <= i < j <= n - 1
    	// nums[i] * nums[j] % k == 0
    	memset(cnt, 0, sizeof(cnt));
    	int n = nums.size(), mx = 0;
    	long long ans = 0;
    	// 随机化的情况下，这个算法复杂度接近于 nlogn 但很容易卡掉
    	for (int i = 0; i < n; ++i) {
    		int g = gcd(nums[i], k), tmp = k / g;
    		for (int j = 1; j * tmp <= mx; ++j) ans += cnt[j * tmp];
    		mx = max(mx, g);
    		++cnt[g];
    	}
    	return ans;
    }
};


// 实际上每一个gcd[i]都是k的因子，那么可以简单的枚举因子就可以了
class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num: nums) {
            ++freq[gcd(num, k)];
        }
        long long ans = 0;
        for (auto&& [x, occx]: freq) {
            for (auto&& [y, occy]: freq) {
                if (static_cast<long long>(x) * y % k == 0) {
                    ans += static_cast<long long>(occx) * occy;
                }
            }
        }
        for (int num: nums) {
            if (static_cast<long long>(num) * num % k == 0) {
                --ans;
            }
        }
        return ans / 2;
    }
};
