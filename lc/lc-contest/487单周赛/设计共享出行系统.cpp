#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class RideSharingSystem {
public:
    set<pii> r, d;
    int t = 0;
    vector<int> tim;
    RideSharingSystem() {
        tim.resize(1005);
    }
    
    void addRider(int riderId) {
        ++t;
        r.emplace(t, riderId);
        tim[riderId] = t;
    }
    
    void addDriver(int driverId) {
        ++t;
        d.emplace(t, driverId);
    }
    
    vector<int> matchDriverWithRider() {
        if (r.empty() || d.empty()) return {-1, -1};
        int x = r.begin()->second, y = d.begin()->second;
        r.erase(r.begin());
        d.erase(d.begin());
        return {y, x};
    }
    
    void cancelRider(int riderId) {
        auto it = r.find({tim[riderId], riderId});
        if (it != r.end()) {
            tim[riderId] = 0;
            r.erase(it);
        }
    }
};

/**
 * Your RideSharingSystem object will be instantiated and called as such:
 * RideSharingSystem* obj = new RideSharingSystem();
 * obj->addRider(riderId);
 * obj->addDriver(driverId);
 * vector<int> param_3 = obj->matchDriverWithRider();
 * obj->cancelRider(riderId);
 */