class Solution {
public:
    int balancedString(string s) {
        // 0 is Q, 1 is W , 2 is E, 3 is R
        unordered_map<char, int> id;
        id['Q'] = 0;
        id['W'] = 1;
        id['E'] = 2;
        id['R'] = 3;
        vector<int> cnt(4);

        for (char ch : s) ++cnt[id[ch]];

        int ans = INT_MAX;
        int sum = 0;
        int n = s.size();
        vector<int> candi;
        vector<int> a(4);
        vector<int> b(4);
        vector<bool> in(4);
        for (int i = 0; i < 4; ++i)
            if (cnt[i] - n / 4 > 0) {
                candi.emplace_back(i);
                in[i] = true;
                a[i] = (cnt[i] - n / 4);
            }
        int m = candi.size();
        int cur = 0;
        int l = 0;
        if (m == 0) return 0;
        for (int i = 0; i < n; ++i) {
            int index = id[s[i]];
            if (in[index]) {
                ++b[index];
                if (b[index] == a[index]) ++cur;
            }
            while (cur == m) {
                ans = min(ans, i - l + 1);
                if (in[id[s[l]]]) --b[id[s[l]]];
                if (b[id[s[l]]] < a[id[s[l]]]) --cur;
                ++l;
            }
        }
        return ans;
    }
};