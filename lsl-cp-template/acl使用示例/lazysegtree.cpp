#include <iostream>
#include <vector>
#include <atcoder/lazysegtree>

using namespace std;
using namespace atcoder;

// 1. 定义树节点存储的数据结构 S
struct S {
    long long value;
    int size; // 区间长度
};

// 2. 定义懒标记的数据结构 F (这里只是简单的加法值)
using F = long long;

// op: 左右子节点合并 (求和)
S op(S a, S b) {
    return {a.value + b.value, a.size + b.size};
}

// e: S 的单位元 (空区间)
S e() {
    return {0, 0};
}

// mapping: 标记 f 作用在节点 x 上 (区间加法：原值 + 增量 * 长度)
S mapping(F f, S x) {
    return {x.value + f * x.size, x.size};
}

// composition: 新标记 f 叠加在旧标记 g 上 (加法直接相加)
// 注意顺序：f 是新来的，g 是原本存在的
F composition(F f, F g) {
    return f + g;
}

// id: 懒标记的单位元 (加 0 等于没加)
F id() {
    return 0;
}

int main() {
    int N, Q;
    cin >> N >> Q;

    // 初始化数组，注意要初始化 size 为 1
    vector<S> a(N, {0, 1}); 

    // 构造线段树
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

    while (Q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            // ACL 的区间是左闭右开 [l, r)
            seg.apply(l, r, x); 
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r).value << endl;
        }
    }
    return 0;
}