// xiaoshulin
// 2023.12.14

class Solution {
public:
    int processTasks(vector<vector<int>> &tasks) {
        sort(tasks.begin(), tasks.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });
        vector<tuple<int, int, int>> st{{-2, -2, 0}}; // 闭区间左右端点，栈底到栈顶的区间长度的和
        for (auto &t : tasks) {
            int start = t[0], end = t[1], d = t[2];
			// 找到最大的一个左边端点小于 start 的区间
            auto[_, r, s] = *--lower_bound(st.begin(), st.end(), start, [](const auto &a, int b) {
                return get<0>(a) < b;
            });
			// 有两种情况: 在区间里面或者区间外面
            d -= get<2>(st.back()) - s; // 去掉运行中的时间点
            if (start <= r) // start 在区间 st[i] 内
                d -= r - start + 1; // 去掉运行中的时间点
            if (d <= 0) continue;
            while (end - get<1>(st.back()) <= d) { // 剩余的 d 填充区间后缀
                auto[l, r, _] = st.back();
                d += r - l + 1; // 合并区间
                st.pop_back();
            }
            st.emplace_back(end - d + 1, end, get<2>(st.back()) + d);
        }
        return get<2>(st.back());
    }
};

