// 经典的表达式模拟题目


class Solution {
public:
    int calculate(string s) {
    	unordered_map<char, int> prio;
    	prio['+'] = 1;
    	prio['-'] = 1;
    	prio['*'] = 2;
    	prio['/'] = 2;

    	stack<int> nums;
    	stack<char> ops;
    	int pos = s.find(" ");
    	while (pos != -1) {
    		s.replace(pos, 1, "");
    		pos = s.find(" ");
    	}
    	auto cal = [&]() {
    		if (nums.size() < 2 || ops.empty()) return;
    		int b = nums.top(); nums.pop();
    		int a = nums.top(); nums.pop();
    		char ch = ops.top(); ops.pop();
    		int ans = 0;
    		if (ch == '-') ans = a - b;
    		else if (ch == '+') ans = a + b;
    		else if (ch == '*') ans = a * b;
    		else ans = a / b;
    		nums.push(ans);
    	};
    	int n = s.size();
    	for (int i = 0; i < n; ++i) {
    		char c = s[i];
    		if (isdigit(c)) {
    			int cur = 0, j = i;
    			while (j < n && isdigit(s[j]))
    				cur = cur * 10 + (s[j++] - '0');
    			nums.push(cur);
    			i = j - 1;
    		} else {
    			if (i > 0 && (s[i - 1] == '-' || s[i - 1] == '+')) 
    				nums.push(0);
    			while (!ops.empty() && prio[ops.top()] >= prio[c])
    				cal();
    			ops.push(c);
    		}
    	}
    	while (!ops.empty()) cal();
    	return nums.top();
    }
};