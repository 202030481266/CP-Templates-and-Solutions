// https://leetcode.cn/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/
// 输出可以包含前导 0 ，但输入保证不会有前导 0


template <class T>
struct fenwick {
    vector<T> t;

    fenwick(int n) : t(n) {}

    void add(int i, T value) {
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
    string minInteger(string num, int k) {
    	int n = num.size();
    	vector<int> pos[10];
    	vector<int> use(10, 0);
    	for (int i = 0; i < n; ++i) pos[num[i] - '0'].emplace_back(i);
    	string ans;
    	// 树状数组求解区间和
    	fenwick<int> tr(n + 10);
    	for (int i = 0; i < n; ++i) {
    		int tmp = -1;
    		for (int x = 0; x <= 9; ++x) {
    			if (use[x] < pos[x].size()) {
    				int idx = pos[x][use[x]], del = tr.sum(idx);
    				if (idx - del <= k) {
    					tmp = x;
    					++use[x];
    					// 减少交换次数
    					tr.add(idx, 1);
    					k -= (idx - del);
    					break;
    				}
    			}
    		}
    		assert(tmp != -1);
    		ans.push_back((char)('0' + tmp));
    	}
    	return ans;
    }
};