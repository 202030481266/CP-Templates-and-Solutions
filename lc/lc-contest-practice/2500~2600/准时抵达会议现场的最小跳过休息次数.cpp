typedef long long ll;
struct Fraction {
    ll x, y;
    Fraction(): x(0), y(0) {}
    Fraction(ll _x, ll _y): x(_x), y(_y) {}
    Fraction operator + (Fraction& rhs) {
        ll nx = y * rhs.x + rhs.y * x;
        ll ny = rhs.y * y;
        ll g = __gcd(nx, ny);
        return Fraction(nx / g, ny / g);
    }
    bool operator < (Fraction& rhs) const {
        return x * rhs.y < y * rhs.x;
    }
    bool operator == (Fraction& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};
class Solution {
    static constexpr ll N = 1e10;
    Fraction dp[1005][1005];
public:
    Fraction ceil(Fraction f) {
        if (f.x % f.y == 0) return Fraction(f.x / f.y, 1);
        return Fraction(f.x / f.y + 1, 1);
    }
    Fraction min(Fraction a, Fraction b) {
        if (a < b) return a;
        return b;
    }
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        int n = dist.size();
        for (int i = 0; i <= n; ++i) dp[0][i] = Fraction(0, 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= n; ++j) dp[i][j] = Fraction(N, 1);
        for (int i = 1; i <= n; ++i) {
            Fraction t(dist[i - 1], speed);
            for (int skip = 0; skip <= i; ++skip) {
                if (skip > 0) {
                    dp[i][skip] = min(ceil(dp[i - 1][skip]), dp[i - 1][skip - 1]) + t;
                }
                else dp[i][0] = ceil(dp[i - 1][0]) + t;
            }
        }
        Fraction h(hoursBefore, 1);
        for (int i = 0; i <= n; ++i) {
            if (dp[n][i] < h || dp[n][i] == h)
                return i;
        }
        return -1;
    }
};