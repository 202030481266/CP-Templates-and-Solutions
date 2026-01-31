class Solution {
public:
    int passThePillow(int n, int time) {
        int a = 2 * (n - 1);
        int b = time % a;
        if (b <= n - 1) return 1 + b; 
        return 2 * n - b - 1;
    }
};