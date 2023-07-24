typedef long long ll;
class Solution {
public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int t, int fu, int pa) {
        ll ans = 0, target = t, full = fu, partial = pa;
        vector<ll> arr;
        for (int& c : flowers) {
            if (c >= target) {
                ans += full;
            }
            else {
                arr.push_back(target - c);
            }
        }
        sort(arr.begin(), arr.end());
        int n = arr.size();
        ll need = 0, pos = n;
        // [0, pos)
        // 可以证明填充完善的花园总是使用需要较少的花园总是最优的（本道题最难的地方）
        for (int i = 0; i < arr.size(); ++i) {
            need += arr[i];
            if (need > newFlowers) {
                pos = i;
                break;
            }
        }
        // calculate [st, n) 
        vector<ll> f;
        ll cnt = 0, res = 0, last = 0, p = -1; 
        auto cal = [&](ll num) -> ll {
            if (f.size() == 0 || num <= 0) return 0;
            f.push_back(1e10);  // 哨兵
            if (p == -1) p = 0;
            else { 
                --cnt;
                num -= last;
            }
            for (int i = p; i < f.size(); ++i) {
                ++cnt;
                res = f[i];
                ll sub = f[i + 1] - f[i];
                if (sub * cnt <= num) {
                    num -= sub * cnt;
                    last += sub * cnt;
                }
                else {
                    p = i;
                    res += num / cnt;
                    break;
                }
            }
            f.pop_back();  // 删除哨兵
            return min(target - 1, res);
        };
        ll tot = 0;
        need = 0;
        for (int i = n - 1; i >= pos; --i) f.push_back(target - arr[i]);
        for (int i = 0; i <= pos - 1; ++i) need += arr[i];
        for (int i = pos - 1; i >= 0; --i) {
            // [0, i] is full
            tot = max(tot, full * (i + 1) + partial * cal(newFlowers - need));
            need -= arr[i];
            f.push_back(target - arr[i]);
        }
        return ans + max(tot, cal(newFlowers) * partial);
    }
};