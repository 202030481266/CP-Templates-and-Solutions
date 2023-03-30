// https://leetcode.cn/problems/kth-smallest-instructions/



class Solution {
public:
	long long binomial(long long n, long long k) {
	    long long res = 1;
	    for (int i = 0; i < k; i++) {
	        res = res * (n - i) / (i + 1);
	    }
	    return res;
	}
    string kthSmallestPath(vector<int>& destination, int k) {
    	int row = destination[0], col = destination[1];

        int n = row + col;

    	// row is numbers of V
    	// col is numbers of H

    	vector C(n + 1, vector<long long>(n + 1));
    	for (int i = 1; i <= n; ++i) {
    		for (int j = 0; j <= i; ++j) {
    			if (C[i][i - j]) C[i][j] = C[i][i - j];
    			else C[i][j] = binomial(i, j);
    		}
    	}
    	string ans;

    	for (int i = 0; i < n; ++i) {
    		if (col == 0 || row == 0) {
    			while (col--) ans.push_back('H');
    			while (row--) ans.push_back('V');
    			break;
    		}
    		// starts from H
    		long long H = C[col + row - 1][col - 1];
    		// starts from V
    		long long V = C[col + row - 1][row - 1];
    		if (k <= H) {
    			ans.push_back('H');
    			--col;
    		}
    		else {
    			ans.push_back('V');
    			--row;
    			k -= H;
    		}
    	}
    	return ans;
    }
};