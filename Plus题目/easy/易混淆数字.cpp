class Solution {
public:
    bool confusingNumber(int n) {
        if (n == 0) return false;
        vector<int> arr;
        int x = n;
        while (x) {
            arr.push_back(x % 10);
            x /= 10;
        }
        vector<int> nums{0, 1, 6, 8, 9};
        vector<int> use(10, 0);
        for (int& v : nums)
            use[v] = 1;
        for (int& v : arr)
            if (!use[v])
                return false;
        unordered_map<int, int> mp = {{0, 0}, {1, 1}, {6, 9}, {8, 8}, {9, 6}};
        string s = to_string(n);
        if (s.size() != arr.size())
            return true;
        bool flag = true;
        for (int i = 0, j = arr.size() - 1; i <= j; ++i, --j) {
            if (arr[j] != mp[arr[i]]) {
                flag = false;
                break;
            }
        }
        return !flag;
    }
};