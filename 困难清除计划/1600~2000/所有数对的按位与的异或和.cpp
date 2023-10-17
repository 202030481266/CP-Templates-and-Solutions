class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size(), m = arr2.size();

        int ans = 0;
        for (int i = 0; i < 32; ++i) {
            int x = 0, y = 0;
            for (int& v : arr1) if ((v >> i) & 1) ++x;
            for (int& v : arr2) if ((v >> i) & 1) ++y;
            if ((x & 1) && (y & 1)) ans += (1 << i);
        }
        return ans;
    }
};