// 高难度模拟题
class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.size();

        // 1 <= n <= 50, 6 <= N <= 20

        // 指定的必须要包含的字符
        bool containLower = false, containDigit = false, containUpper = false;
        for (int i = 0; i < n; ++i) {
            if (isdigit(password[i])) containDigit = true;
            else if (isalpha(password[i])) {
                if (islower(password[i])) containLower = true;
                else containUpper = true;
            }
        }

        // 连续的字符段
        // 对于连续的字符，最高效的方法是替换消除，其次是插入，最后是删除
        vector<pair<int, int>> duplicate;
        int pre = -1;
        for (int i = 0; i < n; ++i) {
            if (pre == -1) pre = i;
            else if (password[pre] != password[i]) {
                // [pre, i)
                if (i - pre >= 3) {
                    duplicate.emplace_back(pre, i);
                }
                pre = i;
            }
        }
        if (n - pre >= 3) duplicate.emplace_back(pre, n);

        // 分类讨论 n 就非常容易调试
        cout << n << endl;

        if (n < 6) {
            // 字符数量不够只能添加
            int cnt = (!containUpper) + (!containLower) + (!containDigit);
            int total = 6 - n, ans = 0; // 至少增加这么多
            // 消除连续的字段
            if (total >= cnt) {
                // 我们至少增加total个字符因此这是最小的答案
                // 唯一可能增加答案的可能性在于消除连续字段
                ans = total;
                for (auto [l, r] : duplicate) {
                    int len = r - l, need = ((len & 1) ? (len + 1) / 2 - 1 : len / 2 - 1);
                    if (total >= need) total -= need;
                    else {
                        need -= total;
                        // 表明还有一个长度为 len - 2 * add 的连续长度串
                        int rem = len - 2 * total;
                        total = 0;
                        ans += (rem / 3);  // 使用替换法高效解决
                    }
                }
            }
            else {
                // 如果缺少的字符的数量比我必定需要添加的还要多，那么我们可以先添加然后使用替换的方法去取代一些原有的连续字段
                // 无论如何我们至少操作cnt次，唯一可能增加答案的可能在于消除连续字段不然就可以选择一直添加
                ans = cnt;
                int sub = cnt - total;
                for (auto [l, r] : duplicate) {
                    int len = r - l, need = ((len & 1) ? (len + 1) / 2 - 1 : len / 2 - 1);
                    if (total >= need) total -= need;
                    else {
                        need -= total;
                        total = 0;
                        // 表明还有一个 len - 2 * add的连续字符串
                        int rem = len - 2 * total, sub_need = rem / 3;
                        if (sub >= sub_need) sub -= sub_need;
                        else {
                            sub_need -= sub;
                            sub = 0;
                            ans += (sub_need);  // 额外添加所剩下的替换次数
                        }
                    }
                }
            }
            return ans;
        }
        else if (n > 20) {
            // 字符数量太多了，只能删除
            int cnt = (!containUpper) + (!containLower) + (!containDigit);
            int total = n - 20, ans = total;
            // 因为替换不能改变字符的数量，所以最优决策必定是先删除足够多的字符后再去进行替换
            // 根据鸽巢原理一定存在合适的位置进行替换
            // 唯一可能增加答案的就是修改连续字符所使用的字符数量，所以我们优先使用删除去改善使用最少代价并且可以稳定减少总体花费的方法
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
            for (auto [l, r] : duplicate) 
                q.emplace((r - l) % 3 + 1, r - l);
            while (total > 0 && !q.empty()) {
                auto [cost, len] = q.top();
                q.pop();
                if (total >= cost) {
                    total -= cost;
                    len -= cost;
                    if (len >= 3)
                        q.emplace(len % 3 + 1, len);
                }
                else {
                    len -= total;
                    total = 0;
                    if (len >= 3)
                        q.emplace(len % 3 + 1, len);
                }
            }
            int need_sub = 0;
            while (!q.empty()) {
                int len = q.top().second;
                q.pop();
                need_sub += len / 3;
            } 

            // 记得加上cnt因为可能最后还是需要替换
            return ans + max(need_sub, cnt);
        }
        else {
            // 字符串长度介于 6 ~ 20 之间，那么我们对于连续字段只需要考虑使用替换的方法
            int cnt = (!containUpper) + (!containLower) + (!containDigit);
            int ans = cnt;
            for (auto [l, r] : duplicate) {
                int len = r - l, need = len / 3;
                if (cnt >= need) cnt -= need;
                else {
                    need -= cnt;
                    ans += (len - 3 * cnt) / 3;
                    cnt = 0;
                }
            }
            return ans;
        }
        return 0;
    }
};