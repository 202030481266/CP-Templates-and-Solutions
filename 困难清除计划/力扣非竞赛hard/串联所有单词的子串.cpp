typedef unsigned long long ull;
class Solution {
    const ull B = 233;
public:
    ull quick_power(ull a, ull b) {
        ull res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a;
            a = a * a;
        }
        return res;
    }
    vector<int> findSubstring(string s, vector<string>& words) {
        int m = words.size(), len = words[0].size(), cnt[m + 1], num[m + 1], tot = 0;
        ull n = s.size(), h[n + 1], H[n + 1];
        ull C = quick_power(B, len);
        h[0] = 0;
        for (int i = 1; i <= n; ++i)
            h[i] = (h[i - 1] * B + (ull)s[i - 1]);
        for (int i = 0; i + len - 1 < n; ++i) {
            // the hash of [i, i + len - 1]
            H[i] = h[i + len] - h[i] * C;
            // cout << "Hash " << i << " is " << H[i] << endl;
        }

        // 计算 words 的 hash 和 num
        unordered_map<ull, int> pos;
        memset(num, 0, sizeof(num));
        for (int k = 0; k < m; ++k) {
            string& vs = words[k];
            ull tmp = 0;
            for (int i = 0; i < len; ++i)
                tmp = tmp * B + (ull)vs[i];
            if (!pos.count(tmp)) pos[tmp] = k, ++tot;
            ++num[pos[tmp]];
        }

        // 子串的hash，使用滑动窗口进行计算
        vector<int> ans;
        for (int st = 0; st < len; ++st) {
            // groups
            int l = st, type = 0;
            memset(cnt, 0, sizeof(cnt));
            type = 0;
            for (int i = st; i + len - 1 < n; i += len) {
                // [i, i + len - 1]
                if (pos.count(H[i])) {
                    int p = pos[H[i]];
                    ++cnt[p];
                    if (cnt[p] > num[p]) --type; // means previous cnt[p] == num[p];
                    while (l <= i && cnt[p] > num[p]) { // make sure cnt[p] <= num[p]
                        if (cnt[pos[H[l]]] == num[pos[H[l]]]) --type;
                        --cnt[pos[H[l]]];
                        l += len;
                    }
                    if (cnt[p] == num[p]) ++type;
                    if (type == tot) ans.push_back(l);
                } 
                else {
                    // absolutely it is not a valid string
                    l = i + len;
                    type = 0;
                    memset(cnt, 0, sizeof(cnt));
                }
            }
        }
        return ans;
    }
};