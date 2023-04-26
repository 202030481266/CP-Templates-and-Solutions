// https://leetcode.cn/problems/maximum-profit-of-operating-a-centennial-wheel/



class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
    	int n = customers.size();

    	vector<int> a;
    	vector<int> on(4);
    	int wait = 0, profit = 0, ans = 0, mxp = 0;
    	for (int i = 0; wait || i < n; ++i) {
    		// the current capsule is ;
    		int cur = (i % 4 ? 4 - i % 4 : 0);  
            // continue running
    		if (i < n)
    			wait += customers[i]; // add the comming passengers
    		int mn = min(wait, 4); // the passengers number
    		on[cur] = mn;
    		wait -= mn;
    		profit += (mn * boardingCost); // get the profit
    		profit -= runningCost;  // rotate

             // if stop...
    		if (profit > mxp) {
                mxp = profit;
                ans = i + 1;
            } 
    	}
    	return (mxp > 0) ? ans : -1;
    }
};