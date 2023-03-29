// https://leetcode.cn/problems/find-substring-with-given-hash-value/



class Solution {
public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
    	int n = s.size();

    	vector<long long> val(k);
    	vector<long long> a(n);

    	val[0] = 1;
    	for (int i = 1; i < k; ++i) {
    		val[i] = val[i - 1] * (power % modulo) % modulo;
    	}
    	// 滑动窗口
    	long long cur = 0;
    	for (int i = n - k, p = 0; i <= n - 1; ++i, ++p) {
    		cur = (cur + (s[i] - 'a' + 1) * val[p] % modulo) % modulo;
    	}
    	int ans = -1;
    	if (cur == hashValue) ans = n - k;
    	for (int i = n - k - 1, j = n - 1; i >= 0; --i, --j) {
    		cur = (cur - (s[j] - 'a' + 1) * val[k - 1] % modulo + modulo) % modulo;
    		cur = cur * power % modulo;
    		cur = (cur + (s[i] - 'a' + 1)) % modulo;
    		if (cur == hashValue) ans = i;
    	}
        assert(ans != -1);
    	return s.substr(ans, k);
    }
};