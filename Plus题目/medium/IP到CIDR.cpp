using ll = long long;
class Solution {
public:
    // 分组
    int msb(ll n) {
        int msb_pos = 0;
        while ((n >> msb_pos) != 1) {
            msb_pos++;
        }
        return msb_pos;
    }
    vector<string> ipToCIDR(string ip, int n) {
        vector<ll> a;
        stringstream ss(ip);
        string num;
        while (getline(ss, num, '.')) {
            a.push_back(stoll(num));
        }

        ll start = 0;
        for (int i = 3; i >= 0; --i) {
            start |= (a[i] << (8 * (3 - i)));
        }

        auto f = [&](ll st, ll len) -> string {
            vector<int> a(4);
            for (int i = 3; i >= 0; --i) {
                a[i] = (st >> (8 * (3 - i))) & 255;
            }
            string res;
            for (int i = 0; i < 4; ++i) {
                res += to_string(a[i]);
                if (i < 3) res.push_back('.');
                else res.push_back('/');
            }
            return res + to_string(len);
        };

        vector<string> ans;
        for (ll i = start; i < start + n;) {
            ll lb = (i == 0 ? LONG_LONG_MAX : (i & -i)), rem = start + n - i; // [i, start + n)
            ll mn = min(lb, rem), ms = msb(mn);
            ans.push_back(f(i, 32 - ms));
            i = i + (1 << ms);
        }
        return ans;
    }
};