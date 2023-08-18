// https://leetcode.cn/problems/count-number-of-rectangles-containing-each-point/



template <class T>
struct fenwick {
    vector<T> t;

    fenwick(int n) : t(n) {}

    void add(int i, T value) {
        for (; i < t.size(); i |= i + 1)
            t[i] += value;
    }

    // sum[0..i]
    T sum(int i) {
        T res{};
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }

    // returns min(p | sum[0..p] >= sum)
    // requires non-negative tree values
    int lower_bound(T sum) {
        int highest_one_bit = 1;
        while (highest_one_bit << 1 <= t.size())
            highest_one_bit <<= 1;
        int pos = 0;
        // 使用倍增的方法来进行查找
        for (size_t blockSize = highest_one_bit; blockSize != 0; blockSize >>= 1) {
            int p = pos + blockSize - 1;
            if (p < t.size() && t[p] < sum) {
                sum -= t[p];
                pos += blockSize;
            }
        }
        return pos;
    }
};
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        int n = rectangles.size(), m = points.size();

        vector<int> ans(m);
        vector<pair<int, int>> a;
        vector<tuple<int, int, int>> b;
        fenwick<int> tree(200);

        for (auto c : rectangles) {
            a.emplace_back(pair<int, int>{c[0], c[1]});
            tree.add(c[1], 1);
        }
        for (int i = 0; i < m; ++i)
            b.emplace_back(tuple<int, int, int>{points[i][0], points[i][1], i});

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int total = n;
        int last = 0;

        for (auto [x, y, id] : b) {
            auto it = lower_bound(a.begin(), a.end(), make_pair(x, -1));
            // find the element that xi >= x
            if (it == a.end()) {
                ans[id] = 0;
            }
            else {
                int pos = it - a.begin();
                for (int i = last; i < pos; ++i) {
                    tree.add(a[i].second, -1);
                    --n;
                }
                last = pos;
                // 0 <= y < y
                ans[id] = n - tree.sum(y - 1);
            }
        }
        return ans;
    }
};