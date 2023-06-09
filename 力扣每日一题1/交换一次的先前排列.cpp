class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& arr) {
        if (is_sorted(arr.begin(), arr.end())) return arr;
        int n = arr.size();
        for (int i = n - 1; i >= 1; --i) {
            if (arr[i - 1] > arr[i]) {
                auto it = lower_bound(arr.begin() + i, arr.end(), arr[i - 1]);
                int val = *prev(it);
                auto first = lower_bound(arr.begin() + i, arr.end(), val);
                swap(arr[i - 1], arr[first - arr.begin()]);
                break;
            }
        }
        return arr;
    }
};