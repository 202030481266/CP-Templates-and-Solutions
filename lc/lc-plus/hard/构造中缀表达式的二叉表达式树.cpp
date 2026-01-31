/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */


// 此题使用两个栈来模拟能够得到最好的性能
// 通用解法


class Solution {
public:
    Node* expTree(string s) {
        int n = s.size();
        stack<Node*> num;
        stack<char> ops;
        unordered_map<char, int> pri = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

        auto cal = [&]() {
            char c = ops.top();
            ops.pop();
            Node* r = num.top(); num.pop();
            Node* l = num.top(); num.pop();
            Node* cur = new Node(c, l, r);
            num.push(cur);
        };

        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (isdigit(c)) {
                num.push(new Node(s[i] - '0'));
            }
            else if (c == '(') ops.push_back(c);
            else if (c == ')') {
                while (ops.top() != '(') cal();
                ops.pop();
            }
            else {
                // operator
                while (!ops.empty() && pri[ops.top()] >= pri[c]) {
                    cal();
                }
                ops.push(c);
            }
        }
        while (!ops.empty()) cal();
        return num.top(); 
    }
};