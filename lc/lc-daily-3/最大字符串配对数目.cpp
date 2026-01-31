class Solution {
public:
    int maximumNumberOfStringPairs(vector<string>& words) {
        // NP完全问题——图的最大边独立集
        // 但是这个问题有特殊性质
        vector<int> cnt(700);
        for (string& s : words) {
            ++cnt[(s[0] - 'a') * 26 + (s[1] - 'a')];
        }
        int ans = 0;
        for (string& s : words) {
            int b = (s[0] - 'a') * 26 + (s[1] - 'a');
            int c = (s[1] - 'a') * 26 + (s[0] - 'a');
            if (b == c) ans += cnt[b] / 2;
            else ans += min(cnt[b], cnt[c]);
            cnt[b] = 0;
            cnt[c] = 0;
        }

        return ans;
    }
};