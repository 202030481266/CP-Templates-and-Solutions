// https://leetcode.cn/problems/minimum-number-of-k-consecutive-bit-flips/
// 贪心技巧：尺取法，就是碰到0就翻转，因为它总是需要翻转的

template<typename T>
struct Fenwick {
	// index from 0 to N - 1
	int N;
	vector<T> vec;

	Fenwick() { N = 0; }
	Fenwick(int n) {
		vec.resize(n);
		N = n;
	}
	void update(int pos, T val) {
		// update a[pos]
		for (; pos < N; pos |= pos + 1) vec[pos] += val;
	}
	T query(int pos) {
		// sum of [0, pos)
		T res = 0;
		for (; pos > 0; pos &= pos - 1) res += vec[pos - 1];
		return res;
	}
	// just for positive value
	int lower_bound(T val) {
		// first position that sum[0...p] >= val
		// empty sum return -1, no position return N
		if (val <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= N && vec[pos + pw - 1] < val)
				pos += pw, val -= vec[pos - 1];
		}
		return pos;
	}
};

class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
    	int n = nums.size();
    	Fenwick<int> tree(n);

    	int ans = 0;
    	for (int i = 0; i + k - 1 < n; ++i) {
    		int ops = tree.query(i + 1);
    		bool flag = ((nums[i] == 1 && (ops % 2 == 1)) || (nums[i] == 0 && (ops % 2 == 0)));
    		if (flag) {
    			++ans;
    			tree.update(i, 1);
    			tree.update(i + k, -1);
    		}
    	}
    	for (int i = n - k + 1; i < n; ++i) {
    		int ops = tree.query(i + 1);
    		if ((nums[i] == 0 && (ops % 2 == 0)) || (nums[i] == 1 && (ops % 2 == 1)))
    			return -1;
    	}
    	return ans;
    }
};