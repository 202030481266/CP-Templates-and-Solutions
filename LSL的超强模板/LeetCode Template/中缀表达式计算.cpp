std::map<char, int> op_priority = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
};
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