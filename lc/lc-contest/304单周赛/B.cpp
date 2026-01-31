class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int n = grades.size();
        int k = sqrt(2 * n);
        if (k * (k + 1) <= n * 2) return k;
        return k - 1;
    }
};