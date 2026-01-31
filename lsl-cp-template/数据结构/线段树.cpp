/*****线段树*****/
/***单次查询 O(logn)***/

/*
 * 最简单的线段树结构
 */

#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
// 这里的大小需要修改
#define Maxn 400010
typedef long long ll;
ll a[Maxn], laz[Maxn];
void pushdown(int rt) {
    ;
} // 向下传递懒标记
void pushup(int rt) {
    ;
} // 向上合并的操作

void build(int rt, int l, int r) {
    if (l == r) {
        cin >> a[rt];
        return;
    }
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int rt, int l, int r, int L, int R, ll w) {
    if (L <= l && r <= R) {
        ;
    } // 懒标记操作更新
    pushdown(rt);
    if (R <= mid) update(lson, L, R, w);
    else if (L > mid) update(rson, L, R, w);
    else {
        update(lson, L, mid, w);
        update(rson, mid + 1, R, w);
    }
    pushup(rt);
}
// 这里的查询函数很灵活，有时需要返回一个结构体
ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return a[rt];
    }
    pushdown(rt);
    if (R <= mid) {
        return query(lson, L, R);
    } else if (L > mid) {
        return query(rson, L, R);
    }
    // 查询答案合并的操作，需要灵活变更
    else {
        return query(lson, L, mid) + query(rson, mid + 1, R);
    }
}

/*
 * 扫描线1：求多个有重叠矩形的面积
 */
#include <stdio.h>

#include <iostream>

#include <algorithm>

#define lson (x << 1)
#define rson (x << 1 | 1)
using namespace std;
const int MAXN = 1e6 + 10;
typedef long long ll;

int n, cnt = 0;
ll x1, y1, x2, y2, X[MAXN << 1];

struct ScanLine {
    ll l, r, h;
    int mark;
    //  mark用于保存权值 (1 / -1)
    bool operator < (const ScanLine & rhs) const {
        return h < rhs.h;
    }
}
line[MAXN << 1];

struct SegTree {
    int l, r, sum;
    ll len;
    //  sum: 被完全覆盖的次数；
    //  len: 区间内被截的长度。
}
tree[MAXN << 2];

void build_tree(int x, int l, int r) {
    //  我觉得最不容易写错的一种建树方法
    tree[x].l = l, tree[x].r = r;
    tree[x].len = 0;
    tree[x].sum = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build_tree(lson, l, mid);
    build_tree(rson, mid + 1, r);
    return;
}
void pushup(int x) {
    int l = tree[x].l, r = tree[x].r;
    if (tree[x].sum /* 也就是说被覆盖过 */ )
        tree[x].len = X[r + 1] - X[l];
    //      更新长度        
    else
        tree[x].len = tree[lson].len + tree[rson].len;
    //      合并儿子信息
}

void edit_tree(int x, ll L, ll R, int c) {
    int l = tree[x].l, r = tree[x].r;
    //  注意，l、r和L、R的意义完全不同
    //  l、r表示这个节点管辖的下标范围
    //  而L、R则表示需要修改的真实区间
    if (X[r + 1] <= L || R <= X[l]) return;
    //  这里加等号的原因：
    //  假设现在考虑 [2,5], [5,8] 两条线段，要修改 [1,5] 区间的sum
    //  很明显，虽然5在这个区间内，[5,8] 却并不是我们希望修改的线段
    //  所以总结一下，就加上了等号
    if (L <= X[l] && X[r + 1] <= R) {
        tree[x].sum += c;
        pushup(x);
        return;
    }
    edit_tree(lson, L, R, c);
    edit_tree(rson, L, R, c);
    pushup(x);
}
int main() {
    scanf("%d", & n);
    for (int i = 1; i <= n; i++) {
        scanf("%lli %lli %lli %lli", & x1, & y1, & x2, & y2);
        X[2 * i - 1] = x1, X[2 * i] = x2;
        line[2 * i - 1] = (ScanLine) {
            x1,
            x2,
            y1,
            1
        };
        line[2 * i] = (ScanLine) {
            x1,
            x2,
            y2,
            -1
        };
        //      一条线段含两个端点，一个矩形的上下边都需要扫描线扫过
    }
    n <<= 1;
    //  直接把 n <<= 1 方便操作
    sort(line + 1, line + n + 1);
    sort(X + 1, X + n + 1);
    int tot = unique(X + 1, X + n + 1) - X - 1;
    //  去重最简单的方法：使用unique！（在<algorithm>库中）
    build_tree(1, 1, tot - 1);
    //  为什么是 tot - 1 ：
    //  因为右端点的对应关系已经被篡改了嘛…
    //  [1, tot - 1]描述的就是[X[1], X[tot]]
    ll ans = 0;
    for (int i = 1; i < n /* 最后一条边是不用管的 */ ; i++) {
        edit_tree(1, line[i].l, line[i].r, line[i].mark);
        //      先把扫描线信息导入线段树
        ans += tree[1].len * (line[i + 1].h - line[i].h);
        //      然后统计面积
    }
    printf("%lli", ans);
    return 0;
}

/*
 * 扫描线2: 求周长并，就是重叠的矩形的周长和
 */
#include <iostream>

#include <stdio.h>

#include <algorithm>

#define lson (x << 1)
#define rson (x << 1 | 1)
using namespace std;
const int MAXN = 2e4;
int n, X[MAXN << 1];
int x1, y1, x2, y2, pre = 0; /* 先初始化为 0 */

struct ScanLine {
    int l, r, h, mark;
    bool operator < (const ScanLine & rhs) {
        if (h == rhs.h)
            return mark > rhs.mark;
        else return h < rhs.h;
    }
    //		如果出现了两条高度相同的扫描线，也就是两矩形相邻
    //		那么需要先扫底边再扫顶边，否则就会多算这条边
    //		这个对面积并无影响但对周长并有影响
    //		hack 数据：2 0 0 4 4 0 4 4 8 输出应为：24
}
line[MAXN];

struct SegTree {
    int l, r, sum, len, c;
    //  c表示区间线段条数
    bool lc, rc;
    //  lc, rc分别表示左、右端点是否被覆盖 
    //  统计线段条数(tree[x].c)会用到
}
tree[MAXN << 2];

void build_tree(int x, int l, int r) {
    tree[x].l = l, tree[x].r = r;
    tree[x].lc = tree[x].rc = false;
    tree[x].sum = tree[x].len = 0;
    tree[x].c = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build_tree(lson, l, mid);
    build_tree(rson, mid + 1, r);
}

void pushup(int x) {
    int l = tree[x].l, r = tree[x].r;
    if (tree[x].sum) {
        tree[x].len = X[r + 1] - X[l];
        tree[x].lc = tree[x].rc = true;
        tree[x].c = 1;
        //      做好相应的标记
    } else {
        tree[x].len = tree[lson].len + tree[rson].len;
        tree[x].lc = tree[lson].lc, tree[x].rc = tree[rson].rc;
        tree[x].c = tree[lson].c + tree[rson].c;
        //      如果左儿子左端点被覆盖，那么自己的左端点也肯定被覆盖；右儿子同理
        if (tree[lson].rc && tree[rson].lc)
            tree[x].c -= 1;
        //      如果做儿子右端点和右儿子左端点都被覆盖，
        //      那么中间就是连续的一段，所以要 -= 1
    }
}

void edit_tree(int x, int L, int R, int c) {
    int l = tree[x].l, r = tree[x].r;
    if (X[l] >= R || X[r + 1] <= L)
        return;
    if (L <= X[l] && X[r + 1] <= R) {
        tree[x].sum += c;
        pushup(x);
        return;
    }
    edit_tree(lson, L, R, c);
    edit_tree(rson, L, R, c);
    pushup(x);
}

ScanLine make_line(int l, int r, int h, int mark) {
    ScanLine res;
    res.l = l, res.r = r,
        res.h = h, res.mark = mark;
    return res;
}
//  POJ 不这样做就会CE，很难受

int main() {
    scanf("%d", & n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d %d", & x1, & y1, & x2, & y2);
        line[i * 2 - 1] = make_line(x1, x2, y1, 1);
        line[i * 2] = make_line(x1, x2, y2, -1);
        X[i * 2 - 1] = x1, X[i * 2] = x2;
    }
    n <<= 1;
    sort(line + 1, line + n + 1);
    sort(X + 1, X + n + 1);
    int tot = unique(X + 1, X + n + 1) - X - 1;
    build_tree(1, 1, tot - 1);
    int res = 0;
    for (int i = 1; i < n; i++) {
        edit_tree(1, line[i].l, line[i].r, line[i].mark);
        res += abs(pre - tree[1].len);
        pre = tree[1].len;
        //      统计横边
        res += 2 * tree[1].c * (line[i + 1].h - line[i].h);
        //      统计纵边
    }
    res += line[n].r - line[n].l;
    //  特判一下枚举不到的最后一条扫描线
    printf("%d", res);
    return 0;
}

/*
 * 线段树骚操作简单总结：
 * 区间替换：直接全部替换，其他的标记全部清零，优先级最高
 * 区间加
 * 区间乘：当一个乘法标记a进来时，mullazy *= a，addlazy *= a；而一个加法标记b进来时，只要addlazy += b即可
 * 区间p次方，一般不会超过3次方
 * 区间连续的合并：最大子段和，连续子段，上升序列。。。。。。
 * 区间开平方：记录区间是否全为1/0，如果不是，就逐个开平方
 * 区间取模：记录区间最小值，小于p的话就return，否则全部逐个取模
 * 区间除：记录区间最大最小值，还有区间和，整除时递归到叶子。如果区间最大最小值相等，说明区间所有数一样，直接打上标记。
 * 
 * 总结：
 * 对于这些题目，就像是之前考的区间与，区间或一样，除法，开方的操作会让各个数字之间越来越相近，最后变成一串一串连续的数字都是一样的，
 * 所以对于这一部分的操作我们一定程度上使用暴力，而如果一段都相等就相当于直接进行区间剪发的操作
 */
const int mod = 10007;
struct TREE {
    ll sum1, sum2, sum3, add, mul, sets;
    //sum1:一次方的和
    //sum2:二次方的和
    //sum3:三次方的和
    //剩下的是标记
}
tree[100005 << 2];
inline void Set(ll sets, int rt, ll i) { //重置标记操作
    tree[rt].sum1 = (sets * i) % mod;
    tree[rt].sum2 = (sets * sets * i) % mod;
    tree[rt].sum3 = (sets * sets * sets * i) % mod;
}
inline void Add(ll add, int rt, ll i) { //加标记操作
    tree[rt].add = (tree[rt].add + add) % mod;
    tree[rt].sum3 = (tree[rt].sum3 + (add * add * add * i % mod) + 3 * add * ((tree[rt].sum2 + tree[rt].sum1 * add) % mod) % mod) % mod;
    tree[rt].sum2 = (tree[rt].sum2 + (add * add * i % mod + (2 * add * tree[rt].sum1) % mod) % mod) % mod;
    tree[rt].sum1 = (tree[rt].sum1 + add * i % mod) % mod;
}
inline void Mul(ll mul, int rt) { //乘标记操作
    tree[rt].mul = (tree[rt].mul * mul) % mod;
    tree[rt].add = (tree[rt].add * mul) % mod;
    tree[rt].sum1 = (tree[rt].sum1 * mul) % mod;
    tree[rt].sum2 = (tree[rt].sum2 * mul * mul) % mod;
    tree[rt].sum3 = (tree[rt].sum3 * mul * mul * mul) % mod;
}
//以上操作在上面又讲
inline void pushup(int rt) { //上传左右儿子的和
    tree[rt].sum1 = (tree[rt << 1].sum1 + tree[rt << 1 | 1].sum1) % mod;
    tree[rt].sum2 = (tree[rt << 1].sum2 + tree[rt << 1 | 1].sum2) % mod;
    tree[rt].sum3 = (tree[rt << 1].sum3 + tree[rt << 1 | 1].sum3) % mod;
}
inline void pushdown(int rt, int i) { //下传标记，注意优先级
    if (tree[rt].sets != 0) {
        ll sets = tree[rt].sets;
        tree[rt].sets = 0;
        tree[rt << 1].sets = tree[rt << 1 | 1].sets = sets;
        Set(sets, rt << 1, i - (i >> 1));
        Set(sets, rt << 1 | 1, (i >> 1));
        tree[rt << 1].add = tree[rt << 1 | 1].add = 0;
        tree[rt << 1].mul = tree[rt << 1 | 1].mul = 1;
    }
    if (tree[rt].mul != 1) {
        ll mul = tree[rt].mul;
        tree[rt].mul = 1;
        Mul(mul, rt << 1);
        Mul(mul, rt << 1 | 1);
    }
    if (tree[rt].add != 0) {
        ll add = tree[rt].add;
        tree[rt].add = 0;
        Add(add, rt << 1, i - (i >> 1));
        Add(add, rt << 1 | 1, i >> 1);
    }
}
inline void update(ll t, ll q, ll L, ll R, int l, int r, int rt) { //更新
    if (tree[rt].mul == 0) tree[rt].mul = 1; //这个是初始化乘法标记用的，循环初始化居然会T，8秒诶，用个memset快了6秒多！
    if (L <= l && r <= R) { //更新到这里就可以停了，记得打标记
        if (q == 1) {
            Add(t, rt, r - l + 1);
        }
        if (q == 2) {
            Mul(t, rt);
        }
        if (q == 3) {
            tree[rt].mul = 1;
            tree[rt].add = 0;
            tree[rt].sets = t;
            Set(t, rt, r - l + 1);
        }
        return;
    }
    pushdown(rt, r - l + 1);
    int mid = (l + r) >> 1;
    if (L <= mid) update(t, q, L, R, l, mid, rt << 1);
    if (mid < R) update(t, q, L, R, mid + 1, r, rt << 1 | 1);
    pushup(rt);
    return;
}
inline ll query(ll t, ll L, ll R, int l, int r, int rt) { //询问
    if (L <= l && r <= R) {
        if (t == 1)
            return tree[rt].sum1;
        if (t == 2)
            return tree[rt].sum2;
        if (t == 3)
            return tree[rt].sum3;
    }
    pushdown(rt, r - l + 1);
    int mid = (l + r) >> 1;
    ll a = 0, b = 0;
    if (L <= mid) a = query(t, L, R, l, mid, rt << 1);
    if (mid < R) b = query(t, L, R, mid + 1, r, rt << 1 | 1);
    return (a + b) % mod;
}
int main() {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(0);
    int n, m;
    while (~scanf("%d%d", & n, & m)) {
        if (n == 0) break;
        memset(tree, 0, sizeof tree);
        while (m--) {
            ll op, x, y, c;
            scanf("%lld%lld%lld%lld", & op, & x, & y, & c);
            if (op != 4) {
                update(c, op, x, y, 1, n, 1);
            } else {
                printf("%lld\n", query(c, x, y, 1, n, 1));
            }
        }
    }
    return 0;
}