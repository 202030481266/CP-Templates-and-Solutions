class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int a = 0, b = 0;
        for (int& p : bills) {
            if (p == 5) ++a;
            else if (p == 10) {
                if (a > 0) {
                    --a;
                    ++b;
                }
                else return false;
            }
            else if (p == 20) {
                if (b > 0 && a > 0) {
                    --a;
                    --b;
                }
                else if (a >= 3) {
                    a -= 3;
                }
                else return false;
            }
        }
        return true;
    }
};