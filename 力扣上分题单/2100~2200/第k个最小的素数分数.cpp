// https://leetcode.cn/problems/k-th-smallest-prime-fraction/



class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
    	// arr: 递增的数组 + 1和若干不相同的素数组成
    	// 为什么是质数：应该是互质，这样就可以不使用gcd，也是为了方便解题
    	// 两种做法，第一就是使用合并k升序的数组或者直接计算所有的然后排序即可
    	int n = arr.size();
    	vector<pair<int, int>> a;
    	for (int i = 0; i < n; ++i)
    		for (int j = i + 1; j < n; ++j) a.emplace_back(arr[i], arr[j]);
    	sort(a.begin(), a.end(), [](const auto& x, const auto& y){
    		return x.first * y.second < y.first * x.second;
    	});
    	return {a[k - 1].first, a[k - 1].second};
    }
};