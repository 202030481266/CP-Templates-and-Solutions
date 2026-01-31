// 惊了，这么简单题目，还真是使用 0子树1 这种结构排序即可暴力过掉
// 复杂度为 O(10^4log(10^4))还是可以轻松过掉 
class Solution {
public:
    string evolutionaryRecord(vector<int>& parents) {
        // 贪心原则，很有意思的一道题目，寻找到一条字典序最小的欧拉路径
        // -1 < parents[i] < i
        int n = parents.size();

        vector<int> g[n];
        for (int i = 1; i < n; ++i) {
            g[parents[i]].push_back(i);
            g[i].push_back(parents[i]);
        }
        // 似乎只能使用 dfs暴力模拟
        function<string(int, int)> dfs = [&](int u, int fa) -> string {
            string res = "";
            priority_queue<string, vector<string>, greater<string>> q;
            for (int& v : g[u]) {
                if (v != fa) {
                    string tmp = dfs(v, u);
                    q.push("0" + tmp + "1");
                }
            }
            while (!q.empty()) {
                res += q.top();
                q.pop();
            }
            return res;
        };
        string ans = dfs(0, -1);
        if (ans == "") return ans;
        int p = ans.size() - 1;
        while (ans[p] == '1') --p;
        return ans.substr(0, p + 1);
    }
};