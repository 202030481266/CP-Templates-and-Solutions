// 题解 https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/solutions/1830911/by-endlesscheng-zai1/
// 题目 https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/

// 运算性质具有非常明显的单调性，增加或者减少都是指数级别的统计问题

/*
	1、 按位或的性质是单调递增的，所有连续子数组的或运算结果会单调递增，由于一般是整数，所有最多有32个数字（0变成1）
	2、 固定左端点，那么对应按位或的结果的右端点的值是可以计算得到的，并且这些右端点在数轴上是连续的
    3、 技巧在于存储结果以及相对应的信息，然后使用递推来求解区间的结果
*/

class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
    	int n = nums.size();
    	vector<int> ans(n);
    	for (int i = 0; i < n; ++i) {
    		ans[i] = 1;
    		for (int j = i - 1; j >= 0 && (nums[j] | nums[i]) != nums[j]; --j) {
    			// 说明nums[j]可以变大，并且是i第一个让他们的结果更加大的
    			nums[j] |= nums[i];
    			ans[j] = i - j + 1;
    		}
    	}
    	return ans;
    }
};

// 下面是更加通用的模板
class Solution {
public:
    vector<int> smallestSubarrays(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<pair<int, int>> ors; // 按位或的值 + 对应子数组的右端点的最小值
        for (int i = n - 1; i >= 0; --i) {
            // 使用了原地去重的技巧
            // 首先把一个0放在后面为了方便添加自己
            ors.emplace_back(0, i);
            ors[0].first |= nums[i];
            int k = 0;
            for (int j = 1; j < ors.size(); ++j) {
                ors[j].first |= nums[i];
                if (ors[k].first == ors[j].first)
                    ors[k].second = ors[j].second; // 合并相同值，下标取最小的
                else ors[++k] = ors[j];
            }
            // 保留前面的k个
            ors.resize(k + 1);
            // 本题只用到了 ors[0]，如果题目改成任意给定数字，可以在 ors 中查找
            ans[i] = ors[0].second - i + 1;
        }
        return ans;
    }
};

// 子数组的按位或不同结果统计 https://leetcode.cn/problems/bitwise-ors-of-subarrays/
// 如果我们计算了所有的i-1为右端点的不同结果，那么就可以计算所有的以i为端点的结果，由于按位或性质，所以所有的结果个数不会超过32个
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
    	int n = arr.size();
    	set<int> res;
    	vector<int> ors;  // 从左到右是单调递减的结果
    	for (int i = n - 1; i >= 0; --i) {
    		ors.emplace_back(0);
    		ors[0] |= arr[i];
    		int k = 0;
    		for (int j = 1; j < ors.size(); ++j) {
    			ors[j] |= arr[i];
    			if (ors[j] != ors[k])
    				ors[++k] = ors[j];
    		}
    		ors.resize(k + 1);
    		for (int v : ors) res.emplace(v);
    	}
    	return res.size();
    }
};


// 找到最接近目标值的函数值 https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/
// 和按位或运算一样，按位与运算的性质也是单调不增的，并且最多结果只有32个
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
    	int n = arr.size();
    	int ans = INT_MAX;
    	vector<int> ors;  // 从左到右是单调递减的结果
    	for (int i = n - 1; i >= 0; --i) {
    		ors.emplace_back(arr[i]);  // 需要把arr[i]放进去
    		ors[0] &= arr[i];
    		int k = 0;
    		for (int j = 1; j < ors.size(); ++j) {
    			ors[j] &= arr[i];
    			if (ors[j] != ors[k])
    				ors[++k] = ors[j];
    		}
    		ors.resize(k + 1);
    		for (int v : ors) ans = min(ans, abs(v - target));
    	}
    	return ans;
    }
};


// 另外的常见的运算性质： gcd，要么至少/2，乘法，要么至少*2 ,都是指数级别的变化