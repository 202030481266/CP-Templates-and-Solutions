class Solution {
public:
    int sortArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> a(n), b(n), pos(n);
        iota(a.begin(), a.end(), 0); // [0, 1, 2, 3, ...n - 1]
        iota(b.begin(), b.begin() + n - 1, 1); //[1, 2, 3, ..n - 1, 0]

        for (int i = 0; i < n; ++i)
            pos[nums[i]] = i;
        vector<bool> vis(n);
        // calculate a
        auto cal = [&](vector<int>& arr) -> int {
            int res = 0;
            fill(vis.begin(), vis.end(), false);
            for (int i = 0; i < n; ++i) {
                if (vis[i]) continue;
                if (nums[i] != arr[i]) {
                    int j = i, l = 0;
                    int flag = (nums[i] == 0);
                    while (!vis[j]) {
                        vis[j] = true;
                        flag |= (nums[j] == 0);
                        j = pos[arr[j]];
                        ++l;
                    }
                    if (flag) res += l - 1;
                    else res += l + 1;
                }
            }
            return res;
        };
        return min(cal(a), cal(b));
    }
};