class Solution {
public:
    bool isValid(string s) {
        vector<int> a;
        for (char ch : s) {
            if (ch == 'c' && a.size() >= 2) {
                if (a[a.size() - 1] == 1 && a[a.size() - 2] == 0) {
                    a.pop_back();
                    a.pop_back();
                }
                else a.emplace_back(ch - 'a');
            }
            else a.emplace_back(ch - 'a');
        }
        return a.size() == 0;
    }
};