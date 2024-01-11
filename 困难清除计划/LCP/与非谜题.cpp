class Solution {
public:
    int getNandResult(int k, vector<int>& arr, vector<vector<int>>& operations) {
        vector<set<int>> s(k);
        int n = arr.size();
        for (int i = 0; i < k; ++i) s[i].insert(-1); // 哨兵
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                if (!((arr[i] >> j) & 1)) {
                    s[j].insert(i); // zero position
                }
            }
        }
        int ans = 0;
        for (auto& op : operations) {
            int type = op[0], x = op[1], y = op[2];
            if (type == 0) {
                for (int i = 0; i < k; ++i) {
                    int pre = ((arr[x] >> i) & 1), aft = ((y >> i) & 1);
                    if (pre != aft) {
                        if (pre == 0) {
                            // 0->1
                            s[i].erase(x);
                        }
                        else {
                            // 1->0
                            s[i].insert(x);
                        }
                    }
                }
                arr[x] = y;
            }
            else {
                int res = 0;
                for (int i = 0; i < k; ++i) {
                    // find the last zero postion
                    int p = *s[i].rbegin(), len = n - 1 - p;
                    if (len == n) { 
                        // (p, n - 1] is all 1, which the input will change the bits
                        if (x % 2 == 0 || n % 2 == 0) {
                            if ((y >> i) & 1) res |= (1 << i);
                        }
                        else {
                            if (!((y >> i) & 1)) res |= (1 << i);
                        }
                    }
                    // odd -> 0, even -> 1
                    else if (len % 2 == 0) {
                        // exist 0, then whatever the input won't change the bits
                        res |= (1 << i);
                    }
                }
                ans ^= res;
            }
        }
        return ans;
    }
};