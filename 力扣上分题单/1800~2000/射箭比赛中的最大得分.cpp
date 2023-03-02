// https://leetcode.cn/problems/maximum-points-in-an-archery-competition/



class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
    	// 射出的箭就一定要拿到分数

    	int N = (1 << 12);
    	int S = 0;
    	int ans = INT_MIN, status = 0;

    	for (int i = 0; i < 12; ++i)
    		if (aliceArrows[i] > 0) S |= (1 << i);

    	for (int i = 0; i < N; ++i) {
    		// check this status is valid
    		int a = 0, b = 0;
    		for (int k = 0; k < 12; ++k) {
    			if ((i >> k) & 1) {
	    			if ((S >> k) & 1)
	    				a += (aliceArrows[k] + 1);
	    			else ++a;
	    			b += k;
	    		}
    		}
    		if (a > numArrows) continue;
    		if (b > ans) {
    			ans = b;
    			status = i;
    		}
    	}
    	vector<int> res(12);
    	int fill_pos = -1;
    	for (int i = 0; i < 12; ++i) {
    		if ((status >> i) & 1) {
    			if ((S >> i) & 1) res[i] = aliceArrows[i] + 1;
    			else res[i] = 1;
    		}
    		else res[i] = 0, fill_pos = i;
    	}
    	int sum = accumulate(res.begin(), res.end(), 0);
    	if (sum < numArrows)
    		res[fill_pos] = numArrows - sum;
    	return res;
    }
};