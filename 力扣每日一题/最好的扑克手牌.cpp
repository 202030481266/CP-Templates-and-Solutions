class Solution {
public:
    string bestHand(vector<int>& ranks, vector<char>& suits) {

        bool flush = true;
        for (int i = 1; i < 5; ++i)
            if (suits[i] != suits[i - 1]) flush = false;
        if (flush) return "Flush";

        bool three = false;
        bool pair = false;
        vector<int> cnt(15, 0);
        for (auto c : ranks) {
            ++cnt[c];
            if (cnt[c] >= 3) three = true;
            if (cnt[c] >= 2) pair = true;
        }
        if (three) return "Three of a Kind";
        if (pair) return "Pair";
        return "High Card";
    }
};