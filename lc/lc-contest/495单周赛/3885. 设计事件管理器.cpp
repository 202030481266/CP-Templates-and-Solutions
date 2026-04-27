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

struct Cmp {
    bool operator()(const pii& a, const pii& b) {
        if (a.first != b.first) return a.first < b.first;  // 第一关键字降序
        return a.second > b.second;                         // 第二关键字升序
    }
};

class EventManager {
public:
    unordered_map<int, int> h;
    unordered_set<int> dead; 
    priority_queue<pii, vector<pii>, Cmp> q;
    EventManager(vector<vector<int>>& events) {
        for (auto& e : events) {
            h[e[0]] = e[1];
            q.emplace(e[1], e[0]);
        }
    }
    
    void updatePriority(int eventId, int newPriority) {
        if (dead.contains(eventId)) return;
        h[eventId] = newPriority;
        q.emplace(newPriority, eventId);
    }
    
    int pollHighest() {
        while (!q.empty() && (dead.contains(q.top().second) || h[q.top().second] != q.top().first)) q.pop();
        int ans = -1;
        if (!q.empty()) {
            ans = q.top().second;
            dead.insert(ans);
            q.pop();
        }
        return ans;
    }
};

/**
 * Your EventManager object will be instantiated and called as such:
 * EventManager* obj = new EventManager(events);
 * obj->updatePriority(eventId,newPriority);
 * int param_2 = obj->pollHighest();
 */