class Solution {
public:
    string rearrangeString(string s, int k) {
        // 可以使用贪心证明一点，当前位置填下剩下最多的字符一定更加优
        int n = s.size();
        string ans;
        vector<int> cnt(26);
        for (char& c : s) ++cnt[c - 'a'];
        vector<int> pre(26, -k); // pre + k <= i
        for (int i = 0; i < n; ++i) {
            int p = -1, mx = 0;
            for (int j = 0; j < 26; ++j) {
                if (pre[j] + k <= i) {
                    if (cnt[j] > mx) {
                        mx = cnt[j];
                        p = j;
                    }
                }
            }
            if (p == -1) return "";
            ans.push_back(char('a' + p));
            --cnt[p];
            pre[p] = i;
        }
        return ans;
    }
};