class Solution {
public:
    string maskPII(string s) {
        int n = s.size();
        bool is_email = s.find("@") == s.npos ? false : true;
        if (is_email) {
            int pos = s.find("@");
            for (int i = 0; i < s.size(); ++i) {
                if (isalpha(s[i])) s[i] = tolower(s[i]);
            }
            string name = s.substr(0, pos);
            string last = s.substr(pos, n - pos);
            string new_name = name.substr(0, 1) + "*****" + name.substr(name.size() - 1, 1);
            return new_name + last;
        }
        string ans;
        for (char ch : s) {
            if (isdigit(ch)) {
                ans.push_back(ch);
            }
        }
        if (ans.size() == 10) {
            return "***-***-" + ans.substr(6, 4);
        }
        if (ans.size() == 11) {
            return "+*-***-***-" + ans.substr(7, 4);
        }
        if (ans.size() == 12) {
            return "+**-***-***-" + ans.substr(8, 4);
        }
        return "+***-***-***-" + ans.substr(9, 4);
    }
};