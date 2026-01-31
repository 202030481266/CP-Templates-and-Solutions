// 模拟


class Solution {
public:
    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
    	int n = arrival.size();
    	priority_queue<int, vector<int>, greater<int>> in, out;

    	int time = 0, i = 0, last = -1;
    	vector<int> ans(n);
    	while (true) {
    		if (i == n && in.empty() && out.empty()) break;
    		while (i < n && arrival[i] == time) {
    			if (state[i] == 0) in.push(i++);
    			else out.push(i++);
    		}
    		if (last == -1 || last == 1) {
    			if (!out.empty()) {
    				ans[out.top()] = time;
    				out.pop();
    				last = 1; // out
    			}
    			else if (!in.empty()) {
    				ans[in.top()] = time;
    				in.pop();
    				last = 0; // in
    			}
    			else last = -1;// not use
    		}
    		else {
    			if (!in.empty()) {
    				ans[in.top()] = time;
    				in.pop();
    				last = 0; // in
    			}
    			else if (!out.empty()) {
    				ans[out.top()] = time;
    				out.pop();
    				last = 1; // out;
    			}
    			else last = -1;
    		}
    		++time;
    	}
    	return ans;
    }
};