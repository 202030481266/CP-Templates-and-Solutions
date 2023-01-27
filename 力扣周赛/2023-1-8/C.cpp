class Solution {
public:
    bool isItPossible(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> a(30, 0), b(30, 0);

        for (auto c : word1) a[c - 'a']++;
        for (auto c : word2) b[c - 'a']++;
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < 26; i++) {
            if (a[i]) cnt1++;
            if (b[i]) cnt2++;
        }
        if (abs(cnt1 - cnt2) >= 3) return false;
        if (cnt1 == cnt2) {
            for (int i = 0; i < 26; i++) {
                if (a[i] && b[i]) return true;
            }
            bool x = false, y = false, z = false, w = false;
            for (int i = 0; i < 26; i++) {
                if (a[i] == 1 && !b[i]) x = true;
                if (!a[i] && b[i] == 1) y = true;
            }
            for (int i = 0; i < 26; i++) {
                if (a[i] >= 2 && !b[i]) z = true;
                if (b[i] >= 2 && !a[i]) w = true;
            }
            return (x && y) || (z && w);
        } else if (abs(cnt1 - cnt2) == 1) {
            if (cnt1 > cnt2) {
                for (int i = 0; i < 26; i++) {
                    if (a[i] >= 2 && !b[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (j == i) continue;
                            if (b[j] >= 2 && a[j]) return true;
                        }
                    }
                }
                for (int i = 0; i < 26; i++) {
                    if (a[i] == 1 && b[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (j == i) continue;
                            if (b[j] >= 2 && a[j]) return true;
                        }
                    }
                }
                for (int i = 0; i < 26; i++) {
                    if (a[i] == 1 && !b[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (i == j) continue;
                            if (b[j] == 1 && a[j]) return true;
                        }
                    }
                }
            } else {
                for (int i = 0; i < 26; i++) {
                    if (b[i] >= 2 && !a[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (j == i) continue;
                            if (a[j] >= 2 && b[j]) return true;
                        }
                    }
                }
                for (int i = 0; i < 26; i++) {
                    if (b[i] == 1 && a[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (j == i) continue;
                            if (a[j] >= 2 && b[j]) return true;
                        }
                    }
                }
                for (int i = 0; i < 26; i++) {
                    if (b[i] == 1 && !a[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (j == i) continue;
                            if (a[j] == 1 && b[j]) return true;
                        }
                    }
                }
            }
        } else {
            if (cnt1 > cnt2) {
                for (int i = 0; i < 26; i++) {
                    if (a[i] == 1 && !b[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (j == i) continue;
                            if (b[j] >= 2 && a[j]) return true;
                        }
                    }
                }
            } else {
                for (int i = 0; i < 26; i++) {
                    if (b[i] == 1 && !a[i]) {
                        for (int j = 0; j < 26; j++) {
                            if (j == i) continue;
                            if (a[j] >= 2 && b[j]) return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};