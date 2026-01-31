class BIT {
private:
    vector<long long> tree;
    int n;

public:
    BIT(int _n) : n(_n), tree(_n + 1) {}
    static constexpr int lowbit(int x) {
        return x & (-x);
    }
    void add(int x, long long d) {
        while (x <= n) {
            tree[x] += d;
            x += lowbit(x);
        }
    }
    void range_add(int l, int r, long long x) {
        add(l, x);
        add(r + 1, -x);
    }
    long long query(int x) const {
        long long ans = 0;
        while (x) {
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
};
class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        vector<long long> sum(n + 1);
        vector<long long> a(n + 1);

        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + stations[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            int left = max(0, i - r - 1);
            int right = min(i + r, n);
            a[i] = sum[right] - sum[left];
        }
        // 需要使用树状数组
        auto f = [&](long long val) {
            BIT tree = BIT(n + 2);
            for (int i = 1; i <= n; i++) tree.add(i, a[i] - a[i - 1]);
            long long need = 0;
            for (int i = 1; i <= n; i++) {
                long long temp = tree.query(i);
                if (temp >= val) continue;
                else {
                    need += (val - temp);
                    if (need > k) return false;
                    tree.range_add(i, min(n, i + 2 * r), val - temp);
                }
            }
            return true;
        };
        long long ans = -1;
        long long lower = *min_element(a.begin() + 1, a.end());
        long long upper = lower + k;
        while (lower <= upper) {
            long long mid = (lower + upper) / 2;
            if (f(mid)) ans = mid, lower = mid + 1;
            else upper = mid - 1;
        }
        return ans;
    }
};