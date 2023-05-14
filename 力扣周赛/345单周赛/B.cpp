class Solution {
public:
    bool doesValidArrayExist(vector<int>& derived) {
        int n = derived.size();
        int x = 1, y = 0;
        for (int c : derived) {
            if (c == 1) x ^= 1, y ^= 1;
        }
        return (x == 1) || (y == 0);
    }
};