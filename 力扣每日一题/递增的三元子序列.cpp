// 判断难度很小
// LIS的变种，本来是要二分的，但是只有三个元素，那么就退化为了常数级别的判断

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(3, INT_MAX);
        for(int i = 0; i < n; i++){
            int t = nums[i];
            if(f[2] < t) return true;
            else if(f[1] < t and t < f[2]) f[2] = t;
            else if(f[1] > t) f[1] = t;
        }
        return false;
    }
};
