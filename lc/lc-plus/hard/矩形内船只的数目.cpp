/**
 * // This is Sea's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Sea {
 *   public:
 *     bool hasShips(vector<int> topRight, vector<int> bottomLeft);
 * };
 */

class Solution {
public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        int ans = 0;
        // cout << topRight[0] << ' ' << topRight[1] << ' ' << bottomLeft[0] <<' ' << bottomLeft[1] << endl;
        if (topRight[0] > bottomLeft[0] || topRight[1] > bottomLeft[1]) {
            // x axis
            int l = bottomLeft[0], r = topRight[0] + 1;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (sea.hasShips(topRight, {mid, bottomLeft[1]})) l = mid;
                else r = mid;
            }
            int p = l;
            l = bottomLeft[1], r = topRight[1] + 1;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (sea.hasShips({p, topRight[1]}, {p, mid})) l = mid;
                else r = mid;
            }
            // cout << p << ' ' << l << endl;
            if (sea.hasShips({p, l}, {p, l})) ++ans;
            if (p - 1 >= bottomLeft[0]) ans += countShips(sea, {p - 1, topRight[1]}, {bottomLeft[0], l});
            if (l > bottomLeft[1]) ans += countShips(sea, {p, l - 1}, bottomLeft);
            return ans;
        }
        else 
            return (sea.hasShips(bottomLeft, bottomLeft));
    }
};