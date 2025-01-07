/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    inline int count(const string &a, const string &b) {
        int res = 0;
        for (int i = 0; i < 6; ++i) {
            if (a[i] == b[i]) {
                res++;
            }
        }
        return res;
    }
    void findSecretWord(vector<string>& words, Master& master) {
        srand(time(0));
        vector<string> candidates;
        for (int i = 0; i < words.size(); ++i) {
            candidates.emplace_back(words[i]);
        }
        while (!candidates.empty()) {
            string word = candidates[rand() % candidates.size()];
            int cnt = master.guess(word);
            if (cnt == 6) {
                return;
            }
            vector<string> temp;
            for (auto &w : candidates) {
                if (count(w, word) == cnt) {
                    temp.emplace_back(w);
                }
            }
            candidates = move(temp);
        }
    }
};
