// https://leetcode.cn/problems/valid-parenthesis-string/
// 使用栈是最好的选择，使用两个栈来分别存储



class Solution {
public:
    bool checkValidString(string s) {
        stack<int> leftStack;
        stack<int> asteriskStack;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c == '(') {
                leftStack.push(i);
            } else if (c == '*') {
                asteriskStack.push(i);
            } else {
            	// 优先使用左括号进行匹配
                if (!leftStack.empty()) {
                    leftStack.pop();
                } else if (!asteriskStack.empty()) {
                    asteriskStack.pop();
                } else {
                    return false;
                }
            }
        }

        // * 匹配剩下的左括号
        while (!leftStack.empty() && !asteriskStack.empty()) {
            int leftIndex = leftStack.top();
            leftStack.pop();
            int asteriskIndex = asteriskStack.top();
            asteriskStack.pop();
            if (leftIndex > asteriskIndex) {
                return false;
            }
        }
        
        return leftStack.empty();
    }
};



// 动态规划做法
// 实际上也很灵活


class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();
        vector<vector<bool>> dp = vector<vector<bool>>(n,vector<bool>(n,false));

        for (int i = 0; i < n; i++) {
            if (s[i] == '*') {
                dp[i][i] = true;
            }
        }

        for (int i = 1; i < n; i++) {
            char c1 = s[i - 1]; 
            char c2 = s[i];
            dp[i - 1][i] = (c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*');
        }

        for (int i = n - 3; i >= 0; i--) {
            char c1 = s[i];
            for (int j = i + 2; j < n; j++) {
                char c2 = s[j];
                if ((c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*')) {
                    dp[i][j] = dp[i + 1][j - 1];
                }
                for (int k = i; k < j && !dp[i][j]; k++) {
                	// k is in [i, j)
                	// can be split into 2 valid string
                    dp[i][j] = dp[i][k] && dp[k + 1][j];
                }
            }
        }
        return dp[0][n - 1];
    }
};

