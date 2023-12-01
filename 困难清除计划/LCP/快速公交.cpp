// 一道很好的最短路问题
// 难点在于算法的复杂度分析
/*
    在一个点只考虑两种情况：①直接走到0 ②到能乘坐某一种公交车的前后两点并乘坐公交车
    证明为什么不用考虑再多走一会再坐公交车，不妨设是向回走，那么有：
    假设本来走k(k>=0 && k<jump[i])步能做公交车i，那么初始所在的位置设为t*jump[i]+k
    如果多走一会，比如走k+m*jump[i]步再坐公交。发现坐公交之前后一种方法代价多了m*jump[i]*inc
    但是下了公交第一种方法只需要用m*inc就可以追回代价，所以不用考虑
*/
class Solution {
    using ll = long long;
    using PLL = pair<ll, ll>;
    const ll M = 1e9 + 7;
public:
    int busRapidTransit(int target, int inc, int dec, vector<int>& jump, vector<int>& cost) {
        int n = jump.size();

        // 声明小顶堆 优先队列：第一属性为 时间 time，第二属性为 当前位置 position
        priority_queue< PLL, vector<PLL>, greater<PLL> > q;
        // 记录哪些位置已经被遍历过
        unordered_set<ll> seen;

        // 先将 target 存入
        q.emplace(0, (ll)target);
        seen.insert(target);

        // 最坏情况下，从 0 直接前进到 target
        ll ans = (ll)inc * target;

        while(!q.empty()) {
            // 弹出队头元素
            auto [time, position] = q.top();
            q.pop();

            // 若当前时间已经比 全局最优时间 大了，就没必要继续搜索了
            if(time >= ans) continue;
            // 从 target 到 position 时间为 time, 从 position 到 0 为 position * inc
            ans = min(ans, time + position * (ll)inc);

            for(int i = 0; i < n; i++) {
                ll feed = position % (ll)jump[i], next = position / (ll)jump[i];
                if(feed == 0) {
                    // 正好在公交车站
                    if(!seen.count(next)) {
                        q.emplace(time + (ll)cost[i], next);
                    }
                } else {
                    // 向左走到公交车站
                    if(!seen.count(next)) {
                        q.emplace(time + cost[i] + (ll)feed * inc, next);
                    }
                    // 向右走到公交车站
                    if(!seen.count(next + 1)) {
                        q.emplace(time + cost[i] + (ll)(jump[i] - feed) * dec, next + 1);
                    }
                }
            }
        }    

        return ans % M;
    }
};


// 下面是渐进时间复杂度正确但是常数巨大的本人做法
// 主要的区别在于下面还有往前走，而对于第一种做法没有往前走
typedef long long ll;
class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int busRapidTransit(int target, int inc, int dec, vector<int>& jump, vector<int>& cost) {
        // 有意思的最短路问题
        // 构造稀疏图
        // 有意思的是图的点数量不会很多: 接近 5 * 100000 的级别
        int n = jump.size();

        unordered_map<int, ll> dis;
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;

        dis[target] = 0;
        ll ans = 1ll * inc * target;

        q.emplace(0, target);

        while (!q.empty()) {
            ll c = q.top().first;
            int u = q.top().second;
            q.pop();
            if (dis[u] != c) continue;
            ans=min(ans,1ll*u*inc+c);
            for (int i = 0; i < n; ++i) {
                int rem = u % jump[i];
                if (!rem) {
                    ll tmp = min(1ll * cost[i], (u - u / jump[i]) * 1ll * inc);
                    int v = u / jump[i];
                    if (!dis[v]) dis[v] = 1e18;
                    if (dis[v] > c + tmp) {
                        // u -> u / jump[i]
                        dis[v] = c + tmp;
                        q.emplace(c + tmp, v);
                    }
                }
                else {
                    if (u - rem > 0) {
                        if (!dis[u - rem]) dis[u - rem] = 1e18;
                        // u -> u - rem
                        if (dis[u - rem] > c + rem * 1ll * inc) {
                            dis[u - rem] = c + rem * 1ll * inc;
                            q.emplace(c + rem * 1ll * inc, u - rem);
                        }
                    }
                    if (u <= target) {
                        int v = u + jump[i] - rem, change = jump[i] - rem;
                        if (!dis[v]) dis[v] = 1e18;
                        if (dis[v] > c + change * 1ll * dec) {
                            dis[v] = c + change * 1ll * dec;
                            q.emplace(c + change * 1ll * dec, v);
                        }
                    }
                }
            }
        }
         
        return ans%mod;
    }
};