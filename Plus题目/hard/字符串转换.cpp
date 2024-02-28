class Solution {
public:
    bool canConvert(string str1, string str2) {
        vector<int> to(26, -1);
        vector<int> from(26, 0);

        int n = str1.size();
        for (int i = 0; i < n; ++i) {
            int x = str1[i] - 'a', y = str2[i] - 'a';
            if (to[x] == -1) {
                to[x] = y;
                ++from[y];
            } else if (to[x] != y)
                return false;
        }
        // 检查是否存在没有用的点
        for (int i = 0; i < 26; ++i) {
            if (to[i] == -1 || (i != to[i] && to[i] == to[to[i]])) // 可以构造出一个没有用的点或者已经存在这个点
                return true;
        }
        // 检查是否存在多元单依赖环
        vector<bool> vis(26, false);
        for (int i = 0; i < 26; ++i) {
            if (vis[i])
                continue;
            int cur = i;
            while (cur != -1 && !vis[cur]) {
                vis[cur] = true;
                cur = to[cur];
            }
            if (cur == i && to[i] != i) {
                // 找到了环
                cur = to[i];
                bool flag = (from[i] > 1);
                while (!flag && cur != i) {
                    flag = (from[cur] > 1);
                    cur = to[cur];
                }
                if (!flag)
                    return false;
            }
        }
        return true;
    }
};