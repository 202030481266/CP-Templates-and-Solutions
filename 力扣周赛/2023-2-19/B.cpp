class Solution {
public:
    int minOperations(int N) {
        vector<int> a;
        int x = N;

        while (x) {
            a.emplace_back(x % 2);
            x /= 2;
        }

        a.emplace_back(0);

        int n = a.size();
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            if (a[i]) {
                ++ans;
                int j = i;
                while (j < n && a[j]) a[j++] = 0;
                if (j > i + 1) a[j] = 1;
            }
        }

        return ans;
    }
};