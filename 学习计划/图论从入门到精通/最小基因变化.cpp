class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        unordered_map<char, int> mp{
            {'A', 0},
            {'C', 1},
            {'G', 2}, 
            {'T', 3}
        };
        int n = bank.size(), start = 0, ed = -1;
        unordered_map<int, int> dis;
        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) {
            int s = 0;
            for (int j = 0; j < 8; ++j) 
                s |= (mp[bank[i][j]] << (2 * j));
            index[s] = i;
            if (endGene == bank[i]) ed = s;
        }
        if (ed == -1) return -1; // not found
        for (int i = 0; i < 8; ++i) start |= (mp[startGene[i]] << (2 * i));
        queue<int> q;
        q.push(start);
        dis[start] = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (cur == ed) return dis[ed];
            for (int i = 0; i < 8; ++i) {
                int c = (cur >> (2 * i)) & 3, a = (cur ^ (c << (2 * i)));
                for (int j = 0; j < 4; ++j) {
                    if (j == c) continue;
                    int b = a | (j << (2 * i));
                    if (index.count(b) && !dis.count(b)) {
                        dis[b] = dis[cur] + 1;
                        q.push(b);
                    }
                }
            }
        }
        return -1;
    }
};