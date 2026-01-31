// 构造，从下往上构造，”空间“越来越小，根据贪心法则，更加有利
// 对于每一层，每一次选择没有被“感染”的方块，如果可以放在更上一层，则放在上一层。
// 如此一来就可以看出很强的规律性

class Solution {
public:
    vector<vector<int>> colorRed(int n) {
        vector<vector<int>> ans;

        vector<int> start{1, 2, 3, 1};
        int cur = 0, all = 1;

        for (int i = n; i >= 1; --i) {
            if (all) {
                for (int j = min(2 * i - 1, start[cur]); j <= 2 * i - 1; j += 2) {
                    ans.push_back({i, j});
                }
            }
            else {
                ans.push_back({i, min(2 * i - 1, start[cur])});
            }
            cur = (cur + 1) % 4;
            all ^= 1;
        }

        return ans;
    }
};