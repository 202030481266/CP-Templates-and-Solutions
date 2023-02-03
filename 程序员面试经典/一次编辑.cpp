class Solution {
public:
    bool oneEditAway(string first, string second) {
        if (first.size() > second.size()) swap(first, second);
        int n = first.size(), m = second.size();
        if (n == m) {
            int cnt = 0;
            for (int i = 0; i < n; ++i)
                if (first[i] != second[i]) ++cnt;
            if (cnt > 1) return false;
        } else {
            if (m - n > 1) return false;
            int cnt = 0, pos = -1;
            for (int i = 0; i < n; ++i) 
                if (first[i] != second[i]) {
                    pos = i;
                    break;
                }
            if (pos == -1) return true;  // it means n is 0
            for (int i = 0; i < pos; ++i) 
                if (first[i] != second[i]) return false;
            for (int i = pos + 1; i < m; ++i)
                if (first[i - 1] != second[i]) return false;
        }
        return true;
    }
};