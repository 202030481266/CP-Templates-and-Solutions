class Solution {
public:
    string robotWithString(string s) {
        int n = s.size();
        stack<char> st;
        vector<int> mn(n);
        mn[n - 1] = s[n - 1] - 'a';
        for (int i = n - 2; i >= 0; --i)
            mn[i] = min(mn[i + 1], s[i] - 'a');
        string ans;
        for (int i = 0; i < n; ++i) {
            st.push(s[i]);
            while (!st.empty() && i + 1 < n && st.top() - 'a' <= mn[i + 1]) {
                ans.push_back(st.top());
                st.pop();
            }
        }
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }
        return ans;
    }
};