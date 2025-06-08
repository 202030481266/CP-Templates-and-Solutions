// https://leetcode.cn/problems/maximize-ysum-by-picking-a-triplet-of-distinct-xvalues/description/

using ll = long long;

class Solution {
public:
    int maxSumDistinctTriplet(vector<int>& x, vector<int>& y) {
        int n = x.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j) {
            return y[i] > y[j];
        });
        int ans = 0;
        vector<int> use;
        for (int id : ids) {
            bool flag = false;
            for (int i : use) {
                if (x[id] == i) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                ans += y[id];
                use.push_back(x[id]);
                if ((int)use.size() == 3) return ans;
            }
        }
        return -1;
    }
};