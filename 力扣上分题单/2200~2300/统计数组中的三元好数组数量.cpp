// https://leetcode.cn/problems/count-good-triplets-in-an-array/



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
	typedef pair<int, int> pii;
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
    	// 关键点1：两者都是 [0, 1, ..., n - 1] 的 排列 。
    	int n = nums1.size(), a[n], b[n];
    	for (int i = 0; i < n; ++i) a[nums1[i]] = i + 1;
    	for (int i = 0; i < n; ++i) b[nums2[i]] = i + 1;
    	vector<pii> tmp;
    	for (int i = 0; i < n; ++i) tmp.emplace_back(a[i], b[i]);
    	sort(tmp.begin(), tmp.end());
    	// 使用树状数组统计
    	fenwick<long long> t1(n + 2), t2(n + 2);
    	long long ans = 0;
    	for (int i = 0; i < n; ++i) t2.add(tmp[i].second, 1);
    	for (int i = 0; i < n; ++i) {
    		t2.add(tmp[i].second, -1);
    		ans += t1.sum(tmp[i].second - 1) * (t2.sum(n) - t2.sum(tmp[i].second));
    		t1.add(tmp[i].second, 1);
    	}
    	return ans;
    }
};