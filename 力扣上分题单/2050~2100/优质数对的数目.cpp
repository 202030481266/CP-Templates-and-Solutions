// https://leetcode.cn/problems/number-of-excellent-pairs/



template <class T>
struct fenwick {
    vector<T> t;

    fenwick(int n) : t(n) {}

    void update(int i, T value) {
        for (; i < t.size(); i |= i + 1)
            t[i] += value;
    }

    // sum[0..i]
    T sum(int i) {
        T res{};
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }

    // returns min(p | sum[0..p] >= sum)
    // requires non-negative tree values
    int lower_bound(T sum) {
        int highest_one_bit = 1;
        while (highest_one_bit << 1 <= t.size())
            highest_one_bit <<= 1;
        int pos = 0;
        // 使用倍增的方法来进行查找
        for (size_t blockSize = highest_one_bit; blockSize != 0; blockSize >>= 1) {
            int p = pos + blockSize - 1;
            if (p < t.size() && t[p] < sum) {
                sum -= t[p];
                pos += blockSize;
            }
        }
        return pos;
    }
};
class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
    	// unique
    	sort(nums.begin(), nums.end());
    	nums.erase(unique(nums.begin(), nums.end()), nums.end());

    	int n = nums.size();
    	vector<int> a(n);

    	fenwick<long long> tree(100);

    	for (int i = 0; i < n; ++i) {
    		int x = nums[i];
    		while (x) {
    			++a[i];
    			x = (x & (x - 1));
    		}
    	}

    	tree.update(a[0], 1);
    	long long ans = 0;
    	for (int i = 1; i < n; ++i) {
    		if (k - a[i] - 1 > 0)
    			ans += (i - tree.sum(k - a[i] - 1));
    		else ans += i;
    		tree.update(a[i], 1);
    	}
        ans *= 2;
    	for (int i = 0; i < n; ++i) {
    		if (2 * a[i] >= k) ++ans;
    	}
    	return ans;
    }
};