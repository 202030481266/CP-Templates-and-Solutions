// 自顶向下搜索
class Solution {
    int n, dp[40][40][1010];
    string s;
    std::map<char, int> op_priority = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };
    int val[40][40];
public:
    int calculate(int a, int b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: return 0;
        }
    }
    bool isOperator(char c) {
        return op_priority.find(c) != op_priority.end();
    }
    int calculateInfix(std::string s) {
        std::stack<int> nums;
        std::stack<char> ops;
        for (size_t i = 0; i < s.size(); ++i) {
            if (std::isspace(s[i]))
                continue;
            else if (std::isdigit(s[i])) {
                size_t j = s.find_first_not_of("0123456789", i);
                std::string num = s.substr(i, j-i);
                nums.push(std::stoi(num));
                i = j - 1;
            }
            else if (isOperator(s[i])) {
                while (!ops.empty() && isOperator(ops.top()) && op_priority[ops.top()] >= op_priority[s[i]]) {
                    int b = nums.top(); nums.pop();
                    int a = nums.top(); nums.pop();
                    nums.push(calculate(a, b, ops.top()));
                    ops.pop();
                }
                ops.push(s[i]);
            }
            else if (s[i] == '(') {
                ops.push(s[i]);
            }
            else if (s[i] == ')') {
                while (ops.top() != '(') {
                    int b = nums.top(); nums.pop();
                    int a = nums.top(); nums.pop();
                    nums.push(calculate(a, b, ops.top()));
                    ops.pop();
                }
                ops.pop();
            }
        }
        while (!ops.empty()) {
            int b = nums.top(); nums.pop();
            int a = nums.top(); nums.pop();
            nums.push(calculate(a, b, ops.top()));
            ops.pop();
        }
        return nums.top();
    }
    int dfs(int l, int r, int v) {
        int& res = dp[l][r][v];
        if (res != -1) return res;
        if (val[l][r] == v) 
            return res = 1;
        res = 0;
        for (int i = l + 1; i < r; i += 2) {
            if (s[i] == '*') {
                if (v == 0) {
                    int tmp1 = dfs(l, i - 1, 0), tmp2 = dfs(i + 1, r, 0);
                    return (res = (tmp1 || tmp2));
                }
                else {
                    for (int x = 1; x <= v; ++x) {
                        if (v % x == 0) {
                            res = (dfs(l, i - 1, x) && dfs(i + 1, r, v / x));
                            if (res) return 1;
                        }
                    }
                }
            }
            else {
                for (int x = 0; x <= v; ++x) {
                    res = (dfs(l, i - 1, x) && dfs(i + 1, r, v - x));
                    if (res) return 1;
                }
            }
        }
        return 0;
    }
    int scoreOfStudents(string S, vector<int>& answers) {
        s = S;
        n = s.size();
        int correct = calculateInfix(s);
        memset(val, -1, sizeof(val));
        memset(dp, -1, sizeof(dp));
        for (int len = 1; len <= n; len += 2) 
            for (int i = 0; i + len - 1 < n; i += 2)
                val[i][i + len - 1] = calculateInfix(s.substr(i, len));
        int ans = 0;
        for (int& t : answers) {
            if (t == correct) ans += 5;
            else if (dfs(0, n - 1, t)) ans += 2;
        }
        return ans;
    }
};



// 自底向上写法
const int N = 35;

class Solution {
private:
    stack<int> num; stack<char> op;
    vector<int> v1; vector<int> v2;
    unordered_set<int> st[N][N];
public:
    void eval(stack<int> &num, stack<char> &op) {
        auto b = num.top(); num.pop();
        auto a = num.top(); num.pop();
        auto c = op.top(); op.pop();
        num.push(a * b);
    }
    unordered_set<int> dfs(int l, int r) {
        if (st[l][r].size())      return st[l][r];
        if (l == r) {
            unordered_set<int> tmp;
            tmp.insert(v1[l]);
            return tmp;
        }
        unordered_set<int> res;
        for (int i = l; i < r; i++) {
            unordered_set<int> s1 = dfs(l, i);
            unordered_set<int> s2 = dfs(i + 1, r);
            char op = v2[i];
            for (auto c1:s1)
                for (auto c2:s2) {
                    if (op == '+' && c1 + c2 <= 1000)
                        res.insert(c1 + c2);
                    if (op == '*' && c1 * c2 <= 1000)
                        res.insert(c1 * c2);
                }
        }
        st[l][r] = res;
        return res;   
    }
    int scoreOfStudents(string s, vector<int>& answers) {
        unordered_map <int, int> mp;
        int n = s.size();
        // 预处理数组
        for (int i = 0; i < n; i++) {
            if (isdigit(s[i])) {
                int j = i;  int res = 0;
                while (j < n && isdigit(s[j]))
                    res = res * 10 + s[j] - '0', j++;
                num.push(res);
                v1.push_back(res);
                i = j - 1;
            } else {
                op.push(s[i]);
                v2.push_back(s[i]);
            }
        }
        unordered_set<int> st = dfs(0, v1.size() - 1);
        // 统计所有因为顺序错误导致的结果错误
        for (auto c:st) 
            mp[c] = 2;
        vector<int> v;
        // 计算求值
        while (!op.empty()) {
            if (op.top() == '*') {
                eval(num, op);
            } else {
                op.pop();
                int t = num.top(); num.pop();
                v.push_back(t);
            }
        }
        while (num.size()) {
            v.push_back(num.top());
            num.pop();
        }
        // res为正确结果
        int res = accumulate(v.begin(), v.end(), 0);
        mp[res] = 5;
        int ans = 0;
        for (auto c:answers)
            ans += mp[c];
        return ans;
    }
};



