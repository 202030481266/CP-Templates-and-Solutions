class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> g[numCourses];
        vector<int> a(numCourses, -1);
        int tot = 0, cnt = 0;
        for (auto &c : prerequisites) {
            g[c[1]].push_back(c[0]);
            if (a[c[0]] == -1) a[c[0]] = 1, ++tot;
            else ++a[c[0]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
            if (a[i] == 0) q.push(i);
        while (!q.empty()) {
            ++cnt;
            int u = q.front();
            q.pop();
            for (int& v : g[u]) {
                --a[v];
                if (a[v] == 0) q.push(v);
            }
        }
        return cnt == tot;
    }
};