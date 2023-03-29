class Solution {
public:
    vector<int> generate_primes_linear_time(int n) {
        vector<int> lp(n + 1);
        vector<int> primes;
        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
                lp[i * primes[j]] = primes[j];
        }
        return primes;
    }
    bool primeSubOperation(vector<int>& nums) {
        int n = nums.size();

        // 假设已经严格上升
        bool flag = true;
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i] >= nums[i + 1]) {
                flag = false;
                break;
            }
        }
        if (flag) return true;

        vector<int> primes = generate_primes_linear_time(1010);
        auto it = lower_bound(primes.begin(), primes.end(), nums[0]);
        if (it != primes.begin()) nums[0] -= *prev(it);
        for (int i = 1; i < n; ++i) {
            if (nums[i] <= nums[i - 1]) return false;
            auto it = lower_bound(primes.begin(), primes.end(), nums[i] - nums[i - 1]);
            if (it != primes.begin()) {
                nums[i] -= *prev(it);
            }
        }
        // for (int i = 0; i < n; ++i) cout << nums[i] << ' ';cout << endl;
        return true;
    }
};