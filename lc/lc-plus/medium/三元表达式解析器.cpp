#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    string parseTernary(string expression) {
        // T, F和数字都是一个字符，那么实际上这个冒号没有很大的作用，只能是分隔符
        stack<char> ops;
        vector<char> num;
        int n = expression.size();
        auto cal = [&]() {
            char op = ops.top();
            ops.pop();
            char b = num.back(); num.pop_back();
            char a = num.back(); num.pop_back();
            num.pop_back(); // (
            if (op == 'T') num.push_back(a);
            else num.push_back(b);
        };
        for (int i = 0; i < n; ++i) {
            if (expression[i] == 'F' || expression[i] == 'T') {
                if (i+1 < n && expression[i+1] == '?') {
                    ops.push(expression[i]);
                    num.push_back('(');
                    i++;
                }
                else {
                    num.push_back(expression[i]);
                    while (!ops.empty() && num.size() >= 3 && num[num.size()-1] !='(' && num[num.size()-2] != '(') cal();
                }
            }
            else {
                if (expression[i] == ':') continue;
                // 剩下的只有可能是数字
                num.push_back(expression[i]);
                while (!ops.empty() && num.size() >= 3 && num[num.size()-1] !='(' && num[num.size()-2] != '(') cal();
            }
        }
        while (!ops.empty()) cal();
        return {num.back()};
    }
};