class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        int N = (1 << n);
        vector<int> gre(N);

        int pos = 0;
        for (int i = 0; i < N; ++i) {
            gre[i] = (i ^ (i >> 1));
            if (gre[i] == start) pos = i;
        }

        if (start == 0) return gre;
        
        vector<int> ans;
        for (int i = pos; i < N; ++i) ans.emplace_back(gre[i]);
        for (int i = 0; i < pos; ++i) ans.emplace_back(gre[i]);
        return ans;
    }
};