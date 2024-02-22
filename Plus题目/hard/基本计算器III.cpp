class Solution {
    unordered_map<char, int> pri = {
        {'+', 1},
        {'-', 1}, 
        {'/', 2},
        {'*', 2}
    };
public:
    int calculate(string s) {
        // 模板题目，中缀表达式实际上非常套路
        // 因为没有空格所以无须单独处理空格
        int n = s.size();
        stack<char> ops;
        stack<int> nums;
        auto cal = [&]() {
            char op = ops.top();
            ops.pop();
            int b = nums.top();
            nums.pop();
            int a = nums.top();
            nums.pop();
            int res;
            if (op == '+') res = a + b;
            else if (op == '-') res = a - b;
            else if (op == '*') res = a * b;
            else res = a / b;
            nums.push(res);
        };
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c == '(') {
                ops.push(c);
            }
            else if (isdigit(c)) {
                int j = i, res = 0;
                while (j < n && isdigit(s[j])) {
                    res = res * 10 + (s[j++] - '0');
                }
                i = j - 1;
                nums.push(res);
            }
            else if (c == ')') {
                while (ops.top() != '(') {
                    cal();
                }
                ops.pop();
            }
            else {
                // is operator
                while (!ops.empty() && ops.top() != '(' && pri[ops.top()] >= pri[c]) {
                    cal();
                }
                ops.push(c);
            }
        }
        while (!ops.empty()) cal();
        return nums.top();
    }
};