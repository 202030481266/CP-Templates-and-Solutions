class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            set<int> a, b;
            for (int j = 0; j <= i; ++j) a.emplace(A[j]);
            for (int j = 0; j <= i; ++j) b.emplace(B[j]);
            for (int v : a)
                if (b.find(v) != b.end()) ++ans[i];
        }
        return ans;
    }
};