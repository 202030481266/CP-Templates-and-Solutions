class Solution {
    int cnt[30], a[20010];
public:
    int maxRepOpt1(string text) {
        int n = text.size(), ans = 0;
        for (int i = 0; i < n; ++i) {
            a[i] = text[i] - 'a';
            ++cnt[a[i]];
        }
        for (int i = 0; i < 26; ++i) {
            if (!cnt[i]) continue;
            int l_left, l_right, l_size = 0;
            int l, r, size = 0;
            int flag = 0; // find 1
            for (int j = 0; j <= n; ++j) {
                if (j == n || a[j] != i) { // 0
                    if (flag) {
                        // try to concat the last seg
                        if (l_size) {
                            if (l == l_right + 2) {
                                ans = max(ans, l_size + size);
                                if (l_size + size < cnt[i]) ans = max(ans, l_size + size + 1);
                            }
                        }
                        // try to borrow one 
                        if (size < cnt[i]) ans = max(ans, size + 1);
                        // no other choice
                        ans = max(ans, size);
                        l_left = l;
                        l_right = j - 1;
                        l_size = size;
                        flag = 0;
                    }
                }
                else {
                    if (flag) ++size;
                    else {
                        flag = 1;
                        l = j;
                        size = 1;
                    }
                }
            }
        }
        return ans;
    }
};