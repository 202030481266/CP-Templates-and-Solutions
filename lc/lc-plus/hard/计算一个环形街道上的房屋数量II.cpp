/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 * };
 */
class Solution {
public:
    int houseCount(Street* street, int k) {
        int ans = 0, cur = 0;

        // 从开着门的房屋开始遍历
        while (!street->isDoorOpen()) 
            street->moveRight();

        while (k--) {
            street->moveRight();
            ++cur;
            if (street->isDoorOpen()) {
                ans = cur;
                street->closeDoor();
            }
        }

        return ans;
    }
};