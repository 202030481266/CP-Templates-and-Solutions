class Solution {
public:
    int closetTarget(vector<string>& words, string target, int startIndex) {
        int ans = -1, n = words.size();

        int pos = startIndex, a = 0, b = 0;
        while (a <= n && words[pos % n] != target) ++pos, ++a;
        pos = startIndex;
        while (b <= n && words[(pos + n) % n] != target) --pos, ++b;
        if (a > n || b > n) return -1;
        return min(a, b);
    }
};