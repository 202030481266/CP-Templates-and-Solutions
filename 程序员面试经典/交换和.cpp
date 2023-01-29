class Solution {
public:
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        int a = 0, b = 0;
        unordered_map<int, bool> bb;
        for (auto c : array1) a += c;
        for (auto c : array2) b += c, bb[c] = true;
        if (abs(a - b) & 1) return {};
        for (auto c : array1)
            if (bb[(2 * c + b - a) / 2]) return {c, (2 * c + b - a) / 2};
        return {};
    }
};