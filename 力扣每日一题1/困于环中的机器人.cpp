class Solution {
public:
    bool isRobotBounded(string s) {
        int n = s.size();

        // 北0南1东2西3
        int x = 0, y = 0, z = 0;

        auto move = [&]() {
            if (z == 0) ++y;
            else if (z == 1) --y;
            else if (z == 2) ++x;
            else --x;
        };
        auto rotate = [&](int flag) {
            // flag=1的时候是顺时针
            if (z == 0) z = (flag ? 2 : 3);
            else if (z == 1) z = (flag ? 3 : 2);
            else if (z == 2) z = (flag ? 1 : 0);
            else z = (flag ? 0 : 1);
        };

        for (int i = 0; i < n; ++i) {
            if (s[i % n] == 'G') move();
            else if (s[i % n] == 'L') rotate(0);
            else rotate(1);
        }
        // 大概率就是有周期性的，只要满足最后的结果方向是和之前不同的，那么重复之前的结果一定会回到原处
        // 那么只要判断方向会最后的位置就可以了
        if (z != 0 || (x == 0 && y == 0)) return true;
        return false;
    }
};