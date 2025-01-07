class Solution {
private:
    // n 个数构成程度为 2^n 的子集和数组 sums
    // 返回值为空表示无解，否则表示有解
    vector<int> dfs(int n, vector<int>& sums) {
        // 递归到 n=1 时，数组中必然一个为 0，另一个为剩下的最后一个数
        // 如果满足该要求，返回剩下的最后一个数，否则返回表示无解的空数组
        if (n == 1) {
            if (sums[0] == 0) {
                return {sums[1]};
            }
            if (sums[1] == 0) {
                return {sums[0]};
            }
            return {};
        }

        int d = sums[1] - sums[0];
        // 双指针构造 s 和 t
        int left = 0, right = 0;
        vector<int> s, t;
        // 记录每个子集和是否选过
        vector<int> used(1 << n);
        while (true) {
            // left 指针找到最小的未被选择过的子集和
            while (left < (1 << n) && used[left]) {
                ++left;
            }
            if (left == (1 << n)) {
                break;
            }
            s.push_back(sums[left]);
            used[left] = true;
            // right 指针找到 sums[left] + d
            while (used[right] || sums[right] != sums[left] + d) {
                ++right;
            }
            t.push_back(sums[right]);
            used[right] = true;
        }
        // 尝试包含 d 并递归求解 (n-1, s)
        vector<int> ans = dfs(n - 1, s);
        if (!ans.empty()) {
            ans.push_back(d);
            return ans;
        }
        // 尝试包含 -d 并递归求解 (n-1, t)
        ans = dfs(n - 1, t);
        if (!ans.empty()) {
            ans.push_back(-d);
            return ans;
        }
        // 无解返回空数组
        return {};
    }

public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        // 提前将数组排好序
        sort(sums.begin(), sums.end());
        return dfs(n, sums);
    }
};