class Solution {
    int cnt[26], sum[2100];
public:
    int cal(string s) {
        memset(cnt, 0, sizeof(cnt));
        for (char c : s) ++cnt[c - 'a'];
        for (int i = 0; i < 26; ++i)
            if (cnt[i]) return cnt[i];
        return 0;
    }
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        memset(sum, 0, sizeof(sum));
        for (auto& s : words) {
            int tmp = cal(s);
            ++sum[tmp];
        }
        for (int i = 1; i <= 2000; ++i) sum[i] += sum[i - 1];
        vector<int> ans;
        int n = words.size();
        for (auto& s : queries) {
            int tmp = cal(s);
            ans.emplace_back(n - sum[tmp]);
        }
        return ans;
    }
};