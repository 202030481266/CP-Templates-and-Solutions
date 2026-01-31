class Solution {
public:
    int distMoney(int money, int children) {
        if (money < children) return -1;

        int ans = 0;
        money -= children;
        if (money < 7) return 0;

        int x = money / 7, y = money % 7;
        if (x > children || (x == children && y > 0)) return children - 1;
        else if (x == children - 1 && y == 3) {
            return x - 1;
        }
        return x;
    }
};