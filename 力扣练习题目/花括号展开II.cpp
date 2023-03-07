// https://leetcode.cn/problems/brace-expansion-ii/



class Solution {
public:
    vector<string> braceExpansionII(string s) {
    	stack<set<string>> num;
    	stack<char> ops;

    	num.push({});

    	auto cal = [&]() {
    		if (num.size() < 2 || ops.empty()) return;
    		auto b = num.top(); num.pop();
    		auto a = num.top(); num.pop();
    		char op = ops.top(); ops.pop();
    		set<string> res;
    		assert(op == ',' || op == '*');
    		if (op == ',') {
    			for (auto v : b) res.emplace(v);
    			for (auto v : a) res.emplace(v);
    		}
    		else {
    			for (auto u : a)
    				for (auto v : b)
    					res.emplace(u + v);
    		}
    		num.emplace(res);
    	};
    	int n = s.size();
    	for (int i = 0; i < n; ++i) {
    		char c = s[i];
    		if (c == '{') {
    			// check add multi operation
    			if (i > 0 && (isalpha(s[i - 1]) || s[i - 1] == '}'))
    				ops.push('*'); // it is most priority

    			ops.push(c);
    		}
    		else if (c == '}') {
    			while (!ops.empty()) {
    				if (ops.top() == '{') {
    					ops.pop();
    					break;
    				}
    				else cal();
    			}
    		}
    		else {
    			if (isalpha(c)) {
    				string cur;
    				int j = i;

    				// check add multi operation
    				if (i > 0 && s[i - 1] == '}') ops.push('*'); 

    				while (j < n && isalpha(s[j])) cur += s[j++];
    				num.emplace(set<string>{cur});
    				i = j - 1;
    			}
    			else {
    				// c == ','
    				while (!ops.empty() && ops.top() != '{') cal();
    				ops.push(c);
    			}
    		}
    	}
    	while (!ops.empty() && ops.top() != '{') cal();
    	vector<string> ans;
    	for (auto v : num.top())
    		ans.emplace_back(v);
    	return ans;
    }
};