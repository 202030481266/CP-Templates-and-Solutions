class Solution {
    int fa[26];
public:
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx < fy) swap(fx, fy);
        fa[fx] = fy;
    }
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        iota(fa, fa + 26, 0);
        for (int i = 0; i < s1.size(); ++i) {
            merge(s1[i] - 'a', s2[i] - 'a');
        }
        string ans;
        for (int i = 0; i < baseStr.size(); ++i) {
            ans.push_back(char('a' + find(baseStr[i] - 'a')));
        }
        return ans;
    }
};