class Solution {
public:
    int reachNumber(int target) {
        // 找规律
        target = abs(target);
        int sq = sqrt(2 * target);
        if (sq * (sq + 1) < 2 * target) ++sq;
        while ((target & 1) ^ (sq * (sq + 1) / 2 & 1)) 
            ++sq;
        return sq;
    }
};