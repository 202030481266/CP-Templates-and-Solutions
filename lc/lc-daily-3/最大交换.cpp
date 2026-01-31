class Solution {
public:
    int maximumSwap(int num) {
        vector<int> arr;
        int x = num;
        while (x) {
            arr.push_back(x % 10);
            x /= 10;
        }
        if (is_sorted(arr.begin(), arr.end())) return num;
        vector<int> mx(arr.size());
        mx[0] = arr[0];
        for (int i = 1; i < arr.size(); ++i)
            mx[i] = max(arr[i], mx[i - 1]);
        bool flag = true;
        for (int i = arr.size() - 1; i >= 0 && flag; --i) {
            if (arr[i] != mx[i]) {
                for (int j = 0; j < i; ++j) {
                    if (arr[j] == mx[i]) {
                        swap(arr[j], arr[i]);
                        flag = false;
                        break;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0, j = 1; i < arr.size(); ++i, j *= 10) {
            ans += arr[i] * j;
        }
        return ans;
    }
};