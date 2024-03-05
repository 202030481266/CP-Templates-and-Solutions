/**
 * Definition for an infinite stream.
 * class InfiniteStream {
 * public:
 *     InfiniteStream(vector<int> bits);
 *     int next();
 * };
 */
class Solution {
public:
    vector<int> prefix_function(vector<int>& s) {
        vector<int> p(s.size());
        int k = 0;
        for (int i = 1; i < s.size(); i++) {
            while (k > 0 && s[k] != s[i])
                k = p[k - 1];
            if (s[k] == s[i])
                ++k;
            p[i] = k;
        }
        return p;
    }
    int findPattern(InfiniteStream* stream, vector<int>& pattern) {
        // 在线的模式匹配算法
        // 由于答案一定在stream的前100000个比特位中，那么就可以知道算法的复杂度只要是线性的就可
        // kmp算法
        vector<int> p = prefix_function(pattern);
        int k = 0, i = 0, tmp, m = pattern.size();
        while (true) {
            tmp = stream->next();
            while (k > 0 && pattern[k] != tmp) k = p[k - 1];
            if (tmp == pattern[k]) ++k;
            if (k == m) return i + 1 - m;
            ++i;
        }
        return -1;
    }
};