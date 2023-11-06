// 爆搜题目，代码难实现
// 去重的话可以使用哈希集合或者使用等效的思想，将连续的左括号或者右括号当作一个块处理
// 这里采用第二种更加好的方法
class Solution {
    vector<string> ans;
public:
    bool valid(string s) {
        int cnt = 0;
        for (char ch : s) {
            if (ch == '(') ++cnt;
            else if (ch == ')') {
                if (cnt) --cnt;
                else return false;
            } 
        }
        return true;
    }
    void dfs(int p, string s, int l, int r) {
        if (l == 0 && r == 0) {
            if (valid(s)) ans.push_back(s);
            return;
        }
        for (int i = p; i < s.size(); ++i) {
            if (i != p && s[i] == s[i - 1]) continue;
            if (l + r > s.size() - i) break;
            if (l > 0 && s[i] == '(') dfs(i, s.substr(0, i) + s.substr(i + 1), l - 1, r);
            if (r > 0 && s[i] == ')') dfs(i, s.substr(0, i) + s.substr(i + 1), l, r - 1);
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        // 似乎字母不是无关紧要的
        // 因为只能是删除括号，所以贪心能够得到最优解
        // 贪心计算最少需要删除的
        int l = 0, r = 0;
        for (char ch : s) {
            if (ch == '(') ++l;
            else if (ch == ')') {
                if (l) --l;
                else ++r;
            }
        }
        dfs(0, s, l, r);
        return ans;
    }
};