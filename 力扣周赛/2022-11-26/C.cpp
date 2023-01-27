class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        vector<int> sum(n + 1), num(n + 1);
        vector<int> a(n + 1);

        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + (customers[i - 1] == 'Y');
            num[i] = num[i - 1] + (customers[i - 1] == 'N');
        }
        a[0] = sum[n];
        for (int i = 1; i <= n; i++) {
            a[i] = sum[n] - sum[i] + num[i - 1];
        }
        int ans = a[0], time = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] < ans) {
                ans = a[i];
                time = i;
            }
        }
        return time;
    }
};