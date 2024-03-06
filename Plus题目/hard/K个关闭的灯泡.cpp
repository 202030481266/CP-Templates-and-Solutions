class Solution {
public:
    int kEmptySlots(vector<int>& bulbs, int k) {
        set<int> s;
        int n = bulbs.size();
        for (int i = 0; i < n; ++i) {
            s.insert(bulbs[i]);
            auto it = s.lower_bound(bulbs[i]);
            if (it != s.begin() && bulbs[i] - *prev(it) - 1 == k) return i + 1;
            if (next(it) != s.end() && *next(it) - bulbs[i] - 1 == k) return i + 1;
        }
        return -1;
    }
};