class Solution {
public:
    // 构造
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        // 逆向思维思考，最后的数字去反推是很简单的
        if (sx > tx || sy > ty) return false;
        while (tx != ty) {
            if (ty > tx) {
                // 会一直相减
                if (sx == tx && ty >= sy && (ty - sy) % tx == 0) return true;
                ty = ty % tx;
                if (ty == 0) ty = tx;
            }
            else {
                if (sy == ty && tx >= sx && (tx - sx) % ty == 0) return true;
                tx = tx % ty;
                if (tx == 0) tx = ty;
            }
        }
        return (tx == sx && ty == sy);
    }
};