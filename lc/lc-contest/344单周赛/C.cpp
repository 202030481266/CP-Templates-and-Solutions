class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>> &queries) {
        int q = queries.size(), cnt = 0;
        vector<int> ans(q), a(n + 2); // 避免讨论下标出界的情况
        for (int qi = 0; qi < q; qi++) {
            int i = queries[qi][0] + 1, c = queries[qi][1]; // 下标改成从 1 开始
            if (a[i]) cnt -= (a[i] == a[i - 1]) + (a[i] == a[i + 1]);
            a[i] = c;
            cnt += (a[i] == a[i - 1]) + (a[i] == a[i + 1]);
            ans[qi] = cnt;
        }
        return ans;
    }
};

