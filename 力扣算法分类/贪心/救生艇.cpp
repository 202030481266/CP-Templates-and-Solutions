// https://leetcode.cn/problems/boats-to-save-people/
// 经典的贪心分配技巧（最大+最小，倒序分配）


class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size();

        sort(people.begin(), people.end());

        int l = 0, r = n - 1, ans = 0;
        while (l <= r) {
            if (people[l] + people[r] > limit) {
                --r;
                ++ans;
            } 
            else {
                ++ans;
                ++l;
                --r;
            }
        }
        return ans;
    }
};