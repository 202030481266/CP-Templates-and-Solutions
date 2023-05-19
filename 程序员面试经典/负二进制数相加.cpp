class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        vector<int> res;
        if (arr1.size() < arr2.size()) return addNegabinary(arr2, arr1);
        int c = 0, i, j;
        for (i = arr2.size() - 1, j = arr1.size() - 1; i >= 0; --i, --j) {
            int s = arr1[j] + arr2[i] + c;
            int r = (s % (-2) + 2) % 2;
            c = (s - r) / (-2);
            res.push_back(r);
        }
        for (; j >= 0; --j) {
            int s = arr1[j] + c;
            int r = (s % (-2) + 2) % 2;
            c = (s - r) / (-2);
            res.push_back(r);
        }
        while (c != 0) {
            int r = (c % (-2) + 2) % 2;
            c = (c - r) / (-2);
            res.push_back(r);
        }
        while (res.size() > 1 && res.back() == 0) res.pop_back();
        reverse(res.begin(), res.end());
        return res;
    }
};