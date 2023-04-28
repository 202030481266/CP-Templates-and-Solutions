class Solution {
    int cnt[26];
public:
    bool equalFrequency(string word) {
        // 暴力枚举删除的字符然后判断次数即可，没必要做复杂的分类讨论
        if (word.size() == 1) return true;
        memset(cnt, 0, sizeof(cnt));
        for (char ch : word) ++cnt[ch - 'a'];
        for (int i = 0; i < 26; ++i) {
            if (cnt[i]) {
                --cnt[i];
                int flag = 1, t = -1;
                for (char ch : word) {
                    if (t == -1 && cnt[ch - 'a'] > 0) t = cnt[ch - 'a'];
                    else if (cnt[ch - 'a'] != t && cnt[ch - 'a'] != 0) { flag = 0; break; }
                }
                if (flag) return true;
                ++cnt[i];
            }
        }
        return false;
    }
};