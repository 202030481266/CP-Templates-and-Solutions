class Solution {
public:
    bool makeStringsEqual(string s, string target) {
        // greedy
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == target[i] && s[i] == '1') return true;
        }
        // 没有对应位置的1相同，可以构造出也就行了
        int x = 0, y = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1' && target[i] == '0') ++x;
            if (s[i] == '0' && target[i] == '1') ++y;
        }
        if (x > 0 && y > 0) return true;
        if (x == 0 && y == 0) return true;
        return false;
    }
};