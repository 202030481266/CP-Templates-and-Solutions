// xiaoshulin
// 2024.1.4

class Solution {
public:
    long long minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost) {
        int dis[26][26];
        memset(dis, 0x3f, sizeof(dis));
        for (int i = 0; i < 26; i++) {
            dis[i][i] = 0;
        }
        for (int i = 0; i < cost.size(); i++) {
            int x = original[i] - 'a';
            int y = changed[i] - 'a';
            dis[x][y] = min(dis[x][y], cost[i]);
        }
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < source.length(); i++) {
            int d = dis[source[i] - 'a'][target[i] - 'a'];
            if (d == 0x3f3f3f3f) {
                return -1;
            }
            ans += d;
        }
        return ans;
    }
};



