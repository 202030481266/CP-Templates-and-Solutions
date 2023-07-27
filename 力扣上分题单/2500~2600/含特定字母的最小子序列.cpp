class Solution {
    stack<char> st;
    int cnt = 0, rem = 0;
    char ch;
public:
    int get_letter() {
        if (st.top() == ch) return cnt - 1;
        else return cnt;
    }
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        int n = s.size();
        ch = letter;
        for (char& c : s) if (c == letter) ++rem;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && s[i] < st.top() && get_letter() + rem >= repetition && st.size() - 1 + n - i >= k) {
                char c = st.top();
                st.pop();
                if (c == ch) --cnt;
            }
            st.push(s[i]);
            if (s[i] == ch) --rem, ++cnt;
        }
        string ans;
        while (!st.empty()) ans.push_back(st.top()), st.pop();
        reverse(ans.begin(), ans.end());
        string res;
        int chance = k - repetition, rep = repetition;
        for (int i = 0; i < ans.size(); ++i) {
            if (chance == 0 && rep == 0) break;
            if (ans[i] == ch) {
                if (rep) {
                    --rep;
                    res.push_back(ans[i]);
                }
                else if (chance) {
                    --chance;
                    res.push_back(ans[i]);
                }
            }
            else {
                if (chance) {
                    --chance;
                    res.push_back(ans[i]);
                }
            }
        }
        return res;
    }

};