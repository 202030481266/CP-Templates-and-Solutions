class Solution {
public:
    int addMinimum(string s) {
        string ans;
        int n = s.size(), p = 0, res = 0;
        ans.push_back('a');
        if (s[0] == 'a') ++p;
        else ++res;
        while (p < s.size()) {
            if (s[p] == 'a') {
                if (ans.back() == 'b') {
                    ans.push_back('c'); ++res;
                }
                else if (ans.back() == 'a') {
                    ans.push_back('b');
                    ans.push_back('c');
                    res += 2;
                }
                ans.push_back('a');
            }
            if (s[p] == 'b') {
                if (ans.back() == 'c') {
                    ans.push_back('a'); ++res;
                }
                else if (ans.back() == 'b') {
                    ans.push_back('c');
                    ans.push_back('a');
                    res += 2;
                }
                ans.push_back('b');
            }
            if (s[p] == 'c') {
                if (ans.back() == 'a') {
                    ans.push_back('b'); ++res;
                }
                else if (ans.back() == 'c') {
                    ans.push_back('a');
                    ans.push_back('b');
                    res += 2;
                }
                ans.push_back('c');
            }
            ++p;
        }
        if (ans.back() == 'a') return res + 2;
        if (ans.back() == 'b') return res + 1;
        return res;
    }
};