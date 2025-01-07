class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        int n = sweetness.size();

        int l = 1, r = accumulate(sweetness.begin(), sweetness.end(), 0) + 1;
        
        auto check = [&](int val) -> bool {
            int len = 0;
            for (int i = 0; i < n; ++i) {
                int sum = 0, j = i;
                while (j < n && sum < val) {
                    sum += sweetness[j++];
                }
                // [i, j)
                if (sum >= val) ++len;
                i = j - 1;
            }
            return len >= k + 1;
        };

        while (l + 1 < r) { // [l, r)
            int mid = (l + r) >> 1;
            if (check(mid)) l = mid;
            else r = mid;
        }
        return l;
    }
};