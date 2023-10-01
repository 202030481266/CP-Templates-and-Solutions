// 写过有史以来最难的计算器模拟题目，可能比状态机好想但是细节更多
typedef map<string, int> V;
typedef vector<map<string, int>> E;
bool same(V a, V b) { // 同样的类型的项
	for (auto [key, value] : a) {
		if (key != "C" && (!b.count(key) || b[key] != value)) return false;
	}
	for (auto [key, value] : b) {
		if (key != "C" && (!a.count(key) || a[key] != value)) return false;
	}
	return true;
}
V add(V a, V b) {
	// 项相加
	V res = a;
	res["C"] = a["C"] + b["C"];
	return res;
}
V mul(V a, V b) {
	// 项的乘法
	V res;
	for (auto [key, value] : a) {
		if (key == "C") {  // 常数项
			res["C"] = b["C"] * a["C"];
		}
		else if (b.count(key)) {
			res[key] = value + b[key];
			b.erase(key);
		}
		else {
			res[key] = value;
		}
	}
	for (auto [key, value] : b) {
		if (key != "C") res[key] = value;
	}
	return res;
}
E add(const E& x, const V& y) {
	E res = x;
	bool flag = false;
	for (int i = 0; i < x.size(); ++i) {
		if (same(x[i], y)) {
			flag = true;
			res[i] = add(x[i], y);
		}
	}
	if (!flag) res.push_back(y);
	return res;
}
E add(const E& x, const E& y) { // x + y
	E res = x;
	for (int i = 0; i < y.size(); ++i) {
		bool flag = false;
		for (int j = 0; j < x.size(); ++j) {
			// 尝试合并同类项
			if (same(x[j], y[i])) {
				flag = true;
				res[j] = add(x[j], y[i]);
			}
		}
		if (!flag) res.push_back(y[i]);
	}
	return res;
}
E sub(const E& x, E& y) {  // x - y
	E res;
	for (V& v : y) v["C"] = -1 * v["C"];
	return add(x, y);

}
E mul(const E& x, const E& y) {  // x * y
	E res;
	for (int i = 0; i < x.size(); ++i)
		for (int j = 0; j < y.size(); ++j) {
			V tmp = mul(x[i], y[j]);
			res = add(res, tmp);
		}
	return res;
}
class Solution {
	unordered_map<string, int> vars;
	std::map<char, int> op_priority = {
	    {'+', 1},
	    {'-', 1},
	    {'*', 2},
	    {'/', 2}
	};
public:
	E cal(E a, E b, char op) {
		switch(op) {
		case '+': return add(a, b);
		case '-': return sub(a, b);
		case '*': return mul(a, b);
		default: return a;
		}
	}
    vector<string> basicCalculatorIV(string s, vector<string>& evalvars, vector<int>& evalints) {
    	for (int i = 0; i < evalints.size(); ++i) vars[evalvars[i]] = evalints[i];
    	stack<E> expressions;
    	stack<char> ops;
    	for (int i = 0; i < s.size(); ++i) {
    		if (isspace(s[i])) continue;
    		else if (s[i] == '(') {
    			ops.push(s[i]);
    		}
    		else if (isdigit(s[i])) {
    			size_t j = s.find_first_not_of("0123456789", i);
	            string num = s.substr(i, j - i);
	            int tmp = stoi(num);
	            V y;
	            E x;
	            y["C"] = tmp;
	            x.push_back(y);
	            expressions.push(x);
	            i = j - 1;
    		}
    		else if (s[i] == '+' || s[i] == '-' || s[i] == '*') {
    			while (!ops.empty() && ops.top() != '(' && op_priority[ops.top()] >= op_priority[s[i]]) {
    				E b = expressions.top(); expressions.pop();
    				E a = expressions.top(); expressions.pop();
    				expressions.push(cal(a, b, ops.top()));
    				ops.pop();
    			}
    			ops.push(s[i]);
    		}
    		else if (s[i] == ')') {
    			while (ops.top() != '(') {
    				E b = expressions.top(); expressions.pop();
    				E a = expressions.top(); expressions.pop();
    				expressions.push(cal(a, b, ops.top()));
    				ops.pop();
    			}
					ops.pop();
    		}
    		else if (isalpha(s[i])) {
    			string var;
    			int j = i;
    			while (isalpha(s[j])) 
    				var.push_back(s[j++]);
    			V tmp;
    			if (vars.count(var))
    				tmp["C"] = vars[var];
    			else {
    				tmp[var] = 1;
    				tmp["C"] = 1;
    			}
    			E x;
    			x.push_back(tmp);
    			expressions.push(x);
    			i = j - 1;
    		}
    	}
    	while (!ops.empty()) {
    		E b = expressions.top(); expressions.pop();
			E a = expressions.top(); expressions.pop();
			expressions.push(cal(a, b, ops.top()));
			ops.pop();
    	}
    	E result = expressions.top();
    	// 超级傻逼的排序
    	vector<pair<int, vector<string>>> ans;
    	vector<string> rs;
    	for (V& v : result) {
    		if (v["C"] == 0) continue;
    		string vs = to_string(v["C"]);
    		vector<string> k;
    		int cnt = 0;
    		for (auto [key, value] : v) 
				if (key != "C") {
					for (int i = 0; i < value; ++i)
						vs.append("*" + key), k.push_back(key);
					cnt += value;
				}
			ans.emplace_back(cnt, k);
			rs.emplace_back(vs);
    	}
    	vector<int> ids(ans.size());
    	iota(ids.begin(), ids.end(), 0);
    	sort(ids.begin(), ids.end(), [&](int i, int j){
    		if (ans[i].first != ans[j].first) 
				return ans[i].first > ans[j].first;
    		// ans[i] < ans[j]
    		return ans[i].second < ans[j].second;
    	});
    	vector<string> arr;
    	for (int& c : ids) arr.push_back(rs[c]);
    	return arr;
    }
};