class Solution {
public:
    int shortestWordDistance(vector<string>& wordsDict, string word1, string word2) {
        int p = 0, ans = INT_MAX, n = wordsDict.size();
        vector<string> s{word1, word2};
        vector<int> cnt(2, -1);
        for (int i = 0; i < n; ++i) {
            if (s[p] == wordsDict[i]) {
                cnt[p] = i;
                if (cnt[p ^ 1] != -1)
                    ans = min(ans, i - cnt[p ^ 1]);
                p ^= 1;
            }
            else if (s[p ^ 1] == wordsDict[i]) {
                p ^= 1;
                cnt[p] = i;
                if (cnt[p ^ 1] != -1)
                    ans = min(ans, i - cnt[p ^ 1]);
                p ^= 1;
            } 
        }
        return ans;
    }
};