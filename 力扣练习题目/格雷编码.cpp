class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> a;
        for (int i = 0; i < (1 << n); ++i)
            a.emplace_back(i ^ (i >> 1));
        return a;
    }
};