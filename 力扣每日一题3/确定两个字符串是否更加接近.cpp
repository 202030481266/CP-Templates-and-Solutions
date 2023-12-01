class Solution {
public:
    bool closeStrings(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        if (n != m) return false;

        vector<int> cnt1(26), cnt2(26);

        for (char& c : word1) ++cnt1[c - 'a'];
        for (char& c : word2) ++cnt2[c - 'a'];

        for (int i = 0; i < 26; ++i)
            if (cnt1[i] && !cnt2[i] || cnt2[i] && !cnt1[i]) return false;

        vector<int> c1, c2;
        for (int i = 0; i < 26; ++i) {
            if (cnt1[i]) c1.push_back(cnt1[i]);
            if (cnt2[i]) c2.push_back(cnt2[i]);
        }
        sort(c1.begin(), c1.end());
        sort(c2.begin(), c2.end());
        if (c1.size() != c2.size()) return false;
        for (int i = 0; i < c1.size(); ++i)
            if (c1[i] != c2[i]) return false;
        return true;
    }
};