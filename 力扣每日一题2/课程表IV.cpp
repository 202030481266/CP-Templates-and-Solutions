class Solution {
    int b[110][110];
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<int> a(numCourses);
        vector g(numCourses, vector<int>{});
        for (auto& c : prerequisites) {
            g[c[0]].push_back(c[1]);
            ++a[c[1]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) 
            if (a[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int&v : g[u]) {
                --a[v];
                b[v][u] = 1;
                for (int i = 0; i <= 100; ++i)
                    b[v][i] |= b[u][i];
                if (a[v] == 0) {
                    q.push(v);
                }
            }
        }
        vector<bool> ans;
        for (auto& q : queries) 
            ans.push_back(b[q[1]][q[0]]);
        return ans;
    }
};