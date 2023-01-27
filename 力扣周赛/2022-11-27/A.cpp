class Solution {
public:
    int pivotInteger(int n) {
        int k = n * n + n;
        int t = sqrt(k / 2);
        if (t * t == (k / 2)) return t;
        else return -1;
    }
};