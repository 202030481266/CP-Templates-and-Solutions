// 博弈论
class Solution {
public:
    bool canAliceWin(vector<string>& a, vector<string>& b) {
        int n = a.size(), m = b.size();
        // 0 is alice, 1 is bob
        int p = a[0][0] - 'a';

        vector<int> arr(27, -1); // 0 is alice big, 1 is bob big, 2 is bob doesn't have, 3 is alice doesn't have
        int i = 0, j = 0;
        while (j < m && b[j][0] - 'a' < p) ++j;
        while (i < n || j < m) {
            while (i < n && a[i][0] - 'a' <= p) ++i;
            while (j < m && b[j][0] - 'a' <= p) ++j;
            bool x = (i > 0 && a[i - 1][0] - 'a' == p), y = (j > 0 && b[j - 1][0] - 'a' == p);
            if (!x && !y) break;
            else if (x && y) {
                if (a[i - 1] > b[j - 1]) arr[p] = 0;
                else arr[p] = 1;
            }
            else if (!x) arr[p] = 3;
            else arr[p] = 2;
            ++p;
        }
        function<int(int, int)> dfs = [&](int p, int who) -> int {
            if (who == 0) {
                // alice
                if (arr[p] == 0 || arr[p] == 2) {
                    if (arr[p + 1] == -1 || arr[p + 1] == 2) return 1;
                    else return dfs(p + 1, 1) ^ 1;
                }
                else if (arr[p] == 1) return dfs(p, 1) ^ 1;
                else return 0;
            }
            else {
                if (arr[p] == 1 || arr[p] == 3) {
                    if (arr[p + 1] == -1 || arr[p + 1] == 3) return 1;
                    else return dfs(p + 1, 0) ^ 1;
                }
                else if (arr[p] == 0) return dfs(p, 0) ^ 1;
                else return 0;
            }
        };
        return dfs(a[0][0] - 'a', 0);
    }
};