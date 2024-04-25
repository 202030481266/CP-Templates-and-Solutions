class Solution {
public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        int m = quantities.size();

        int l = 0, r = *max_element(quantities.begin(), quantities.end());

        auto check = [&](int val) -> bool {
            int res = 0;
            for (int& q : quantities) {
                res += (q - 1) / val + 1;
                if (res > n) return false;
            }
            return true;
        };

        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }

        return r;
    }
};