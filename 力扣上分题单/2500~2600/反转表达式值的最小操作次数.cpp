typedef pair<int, int> pii;
class Solution {
public:
    std::map<char, int> op_priority = {
        {'|', 1},
        {'&', 1},
    };
    pii calculate(pii a, pii b, char op) {
        if (op == '|') {
            int zero = min(a.first + b.first, 1 + min(a.first, b.first));
            int one = min(min(a.second, b.second), 1 + a.second + b.second);
            return {zero, one};
        }
        else {
            int zero = min(min(a.first, b.first), 1 + a.first + b.first);
            int one = min(a.second + b.second, 1 + min(a.second, b.second));
            return {zero, one};
        }
    }
    bool isOperator(char c) {
        return op_priority.find(c) != op_priority.end();
    }
    pii calculateInfix(std::string s) {
        std::stack<pii> nums;
        std::stack<char> ops;
        for (size_t i = 0; i < s.size(); ++i) {
            if (std::isspace(s[i]))
                continue;
            else if (std::isdigit(s[i])) {
                size_t j = s.find_first_not_of("0123456789", i);
                std::string num = s.substr(i, j-i);
                int tmp = std::stoi(num);
                if (tmp == 0) {
                    nums.emplace(0, 1);
                }
                else nums.emplace(1, 0);
                i = j - 1;
            }
            else if (isOperator(s[i])) {
                while (!ops.empty() && isOperator(ops.top()) && op_priority[ops.top()] >= op_priority[s[i]]) {
                    auto b = nums.top(); nums.pop();
                    auto a = nums.top(); nums.pop();
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
                    auto b = nums.top(); nums.pop();
                    auto a = nums.top(); nums.pop();
                    nums.push(calculate(a, b, ops.top()));
                    ops.pop();
                }
                ops.pop();
            }
        }
        while (!ops.empty()) {
            auto b = nums.top(); nums.pop();
            auto a = nums.top(); nums.pop();
            nums.push(calculate(a, b, ops.top()));
            ops.pop();
        }
        return nums.top();
    }
    int minOperationsToFlip(string s) {
        int n = s.size();
        auto res = calculateInfix(s);
        cout << res.first << ' ' << res.second << endl;
        if (res.first > 0) return res.first;
        return res.second;
    }
};