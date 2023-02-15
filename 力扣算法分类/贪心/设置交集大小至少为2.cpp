// https://leetcode.cn/problems/set-intersection-size-at-least-two/
// 贪心技巧： 按照区间排序，然后从区间右端点选取最前面就行了
// 懒惰更新： 往上更新的时候碰到不能更新直接退出


class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& in) {
        int n = in.size();
        int ans = 0;

        sort(in.begin(), in.end(), [&](const vector<int>& a, vector<int>& b){
            return (a[1] == b[1]) ? (a[0] > b[0]) : (a[1] < b[1]);
        });

        vector<vector<int>> a(n);
        for (int i = 0; i < n; ++i) {
            for (int j = in[i][1], k = a[i].size(); k < 2; --j, ++k) {
                ++ans;
                for (int x = i + 1; x < n; ++x) {
                    if (in[x][0] > j) break;
                    a[x].emplace_back(j);
                }
            }
        }
        return ans;
    }
};

