class Solution {
public:
    bool canChange(string start, string target) {
        int n = start.size(), j = 0;
        for (int i = 0; i < n; ++i) {
            // match target[i];
            if (target[i] == '_') continue;
            while (j < n && start[j] == '_') ++j;
            if (j == n || start[j] != target[i]) return false;
            else {
                if (target[i] == 'L') {
                    if (j < i) return false;
                }
                if (target[i] == 'R') {
                    if (j > i) return false;
                }
                ++j;
            }
        }
        while (j < n && start[j] == '_') ++j;
        return j == n;
    }
};