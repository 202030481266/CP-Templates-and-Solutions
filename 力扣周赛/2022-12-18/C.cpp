class Solution {
public:
    bool isPossible(int n, vector<vector<int>>& edges) {
        vector<int> du(n + 1, 0);
        vector<int> odd;
        map<pair<int,int>,bool> hash;

        for (auto c : edges) {
            ++du[c[0]], ++du[c[1]];
            hash[make_pair(c[0], c[1])] = true;
            hash[make_pair(c[1], c[0])] = true;
        }
        for (int i = 1; i <= n; i++) {
            if (du[i] & 1) odd.emplace_back(i);
        }
        int m = odd.size();
        if (m & 1 || m > 4) return false;
        else if (m == 0) return true;
        else if (m == 2) {
            bool t = hash[make_pair(odd[0], odd[1])];
            if (!t) return true;
            else {
                for (int i = 1; i <= n; i++) {
                    if (i == odd[0] || i == odd[1]) continue;
                    if (!hash[make_pair(i, odd[0])] && !hash[make_pair(i, odd[1])]) return true;
                }
                return false;
            }
        } else {
            bool t1 = hash[make_pair(odd[0], odd[1])] || hash[make_pair(odd[2], odd[3])];
            bool t2 = hash[make_pair(odd[0], odd[2])] || hash[make_pair(odd[1], odd[3])];
            bool t3 = hash[make_pair(odd[0], odd[3])] || hash[make_pair(odd[1], odd[2])];
            if (!t1 || !t2 || !t3) return true;
            else return false;
        }
    }
};