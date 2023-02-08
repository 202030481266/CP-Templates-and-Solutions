// https://leetcode.cn/problems/integer-replacement/
// 此题的贪心解法非常灵活，主要还是使用动态规划好想一点


// 贪心，选择的优劣可以使用除以2的次数来判断，因为除以2可以快速缩小规模，证明比较复杂
class Solution {
public:
    int integerReplacement(int nn) {
    	auto f = [&](long long k) -> int {
    		if (k == 2) return INT_MAX;
    		int cnt = 0;
    		while (k % 2 == 0) ++cnt, k >>= 1;
    		return cnt;
    	}; 
    	int ans = 0;
    	long long n = nn;
    	while (n != 1) {
    		if (n & 1) {
    			if (f(n + 1) > f(n - 1)) ++n;
    			else --n;
    		}
    		else n >>= 1;
    		++ans;
    	}
    	return ans;
    }
};


// 动态规划
class Solution {
private:
    unordered_map<int, int> memo;

public:
    int integerReplacement(int n) {
        if (n == 1) {
            return 0;
        }
        if (memo.count(n)) {
            return memo[n];
        }
        if (n % 2 == 0) {
            return memo[n] = 1 + integerReplacement(n / 2);
        }
        return memo[n] = 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
    }
};
