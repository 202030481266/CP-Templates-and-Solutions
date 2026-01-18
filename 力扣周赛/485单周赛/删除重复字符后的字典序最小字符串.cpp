#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;


class Solution {
public:
    string lexSmallestAfterDeletion(string s) {
        int n = s.size();
        vi cnt(26);
        for (char c : s) cnt[c - 'a']++;
        stack<char> st;
        for (char c : s) {
            while (!st.empty() && c < st.top() && cnt[st.top() - 'a'] > 1) {
                cnt[st.top() - 'a']--;
                st.pop();
            }
            st.push(c);
        }
        string ans;
        while (!st.empty() && cnt[st.top() - 'a'] > 1) {
            cnt[st.top() - 'a']--;
            st.pop();
        }
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};


