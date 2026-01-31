// 表达式问题总结（基本上都离不开栈这个玩意ば）
// 最简单的最经典的就是逆波兰表达式问题
namespace myExpression {
    // 输入词素（token）然后进行计算
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" ||
                tokens[i] == "*" || tokens[i] == "/") {
                int num1 = st.top(); st.pop();
                int num2 = st.top(); st.pop();
                if (tokens[i] == "+") st.push(num2 + num1);
                if (tokens[i] == "-") st.push(num2 - num1);
                if (tokens[i] == "*") st.push(num2 * num1);
                if (tokens[i] == "/") st.push(num2 / num1);
            }
            else {
                // stoi：字符串转整型
                st.push(stoi(tokens[i]));
            }
        }
        int result = st.top(); st.pop();
        return result;
    }
    // 表达式的形式来进行解析（不是词素了，实际上就是中缀表达式）
    // 通常来说有两种方法：解析词素或者使用两个栈来模拟
    // 基本计算器1：包含 + - ( )
    int calculate1(string s) {
        stack<int> nums;
        stack<char> ops;
        nums.push(0);
        int pos = s.find(" ");

        auto cal = [&]() {
            if (nums.size() < 2 || ops.empty()) return;
            int b = nums.top(); nums.pop();
            int a = nums.top(); nums.pop();
            char op = ops.top(); ops.pop();
            nums.push(op == '+' ? a + b : a - b);
        };
        while (pos != -1) {
            s.replace(pos, 1, "");
            pos = s.find(" ");
        }
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c == '(') ops.push(c);
            else if (c == ')') {
                while (!ops.empty()) {
                    if (ops.top() == '(') {
                        ops.pop();
                        break;
                    }
                    else {
                        cal();
                    }
                }
            }
            else {
                if (isdigit(c)) {
                    int cur = 0;
                    int j = i;
                    while (j < n && isdigit(s[j]))
                        cur = cur * 10 + (s[j++] - '0');
                    nums.push(cur);
                    i = j - 1;
                }
                else {
                    // 最重要的技巧： 补全操作数
                    if (i > 0 && (s[i - 1] == '(' || s[i - 1] == '-' || s[i - 1] == '+'))
                        nums.push(0);
                    while (!ops.empty() && ops.top() != '(')
                        cal();
                    ops.push(c);
                }
            }
        }
        while (!ops.empty()) cal();
        return nums.top();
    }
    // 基本计算器2：包含 + - / *
    int calculate2(string s) {
        stack<int> nums;
        stack<char> ops;
        nums.push(0);
        int pos = s.find(" ");

        auto cal = [&]() {
            if (nums.size() < 2 || ops.empty()) return;
            int b = nums.top(); nums.pop();
            int a = nums.top(); nums.pop();
            char op = ops.top(); ops.pop();
            if (op == '*') nums.push(a * b);
            else if (op == '/') nums.push(a / b);
            else nums.push(op == '+' ? a + b : a - b);
        };
        while (pos != -1) {
            s.replace(pos, 1, "");
            pos = s.find(" ");
        }
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (isdigit(c)) {
                int cur = 0;
                int j = i;
                while (j < n && isdigit(s[j]))
                    cur = cur * 10 + (s[j++] - '0');
                nums.push(cur);
                i = j - 1;
                // 计算乘法或者除法
                while (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) cal();
            }
            else {
                if (c == '*' || c == '/') ops.push(c);
                else {
                    if (i > 0 && (s[i - 1] == '-' || s[i - 1] == '+')) nums.push(0);
                    while (!ops.empty()) cal();
                    ops.push(c);
                }
            }
        }
        while (!ops.empty()) cal();
        return nums.top();
    }
    // 基本计算器3：包含 + - / * % ^ ( ) 
    int calculate3(string s) {
        stack<int> nums;
        stack<char> ops;
        nums.push(0);
        // 去除空格
        int pos = s.find(" ");
		while (pos != -1) {
            s.replace(pos, 1, "");
            pos = s.find(" ");
        }
        unordered_map<char, int> priority;
        priority['+'] = 1;
        priority['-'] = 1;
        priority['*'] = 2;
        priority['/'] = 2;
        priority['%'] = 2;
        priority['^'] = 3;
        auto cal = [&]() {
            if (nums.size() < 2 || ops.empty()) return;
            int b = nums.top(); nums.pop();
            int a = nums.top(); nums.pop();
            char op = ops.top(); ops.pop();
            int ans = 0;
            if (op == '-') ans = a - b;
            else if (op == '+') ans = a + b;
            else if (op == '*') ans = a * b;
            else if (op == '/') ans = a / b;
            else if (op == '^') ans = pow(a, b);
            else if (op == '%') ans = a % b;
            nums.push(ans);
        };
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c == '(') ops.push(c);
            else if (c == ')') {
                while (!ops.empty()) {
                    if (ops.top() == '(') {
                        ops.pop();
                        break;
                    }
                    else {
                        cal();
                    }
                }
            }
            else {
                if (isdigit(c)) {
                    int cur = 0; 
                    int j = i;
                    while (j < n && isdigit(s[j])) cur = cur * 10 + (s[j++] - '0');
                    nums.push(cur);
                    i = j - 1;
                }
                else {
                    // 处理前缀 + - 的特殊存在
                    if (i > 0 && (s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-')) nums.push(0);
                    // 按照优先级把能够计算的都计算了，剩下的都是优先级比现在要放入的符号地
                    while (!ops.empty() && ops.top() != '(') {
                        char prev = ops.top();
                        if (priority[prev] >= priority[c]) cal();
                        else break;
                    }
                    ops.push(c);
                }
            }
        }
        while (!ops.empty() && ops.top() != '(') cal();
        return nums.top();
    }
}