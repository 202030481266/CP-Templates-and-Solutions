#include <bits/stdc++.h>
using namespace std;

// 模板配置区，可随时 Hack 和修改
const int MAX_VERSIONS = 200005; // 最大版本数 (通常等于操作/插入数)
const int MAX_BITS = 30;         // 01-Trie 的最大位数 (30 适用于 1e9 以内的整数)
const int SIGMA = 2;             // 字符集大小 (2为01字典树，如果是小写字母多路设为26)

// MAX_NODES = 最大版本数 * 每次插入新增的节点数 (MAX_BITS + 1) + 1(基础空节点0)
const int MAX_NODES = MAX_VERSIONS * (MAX_BITS + 2); 

struct PersistentTrie {
    int ch[MAX_NODES][SIGMA]; // ch[u][c] 表示节点 u 的第 c 个儿子的节点编号
    int cnt[MAX_NODES];       // cnt[u] 表示经过节点 u 的元素个数（用于持久化区间相减）
    int root[MAX_VERSIONS];   // root[i] 记录第 i 个版本的根节点编号
    int tot;                  // 节点分配器

    // 高效初始化，专为 Multi test case 设计
    void init() {
        tot = 0;
        // 只需要清空 0 号节点（空节点/哨兵）。其余节点全靠懒分配覆写，无需 memset
        cnt[0] = 0;
        for (int i = 0; i < SIGMA; ++i) {
            ch[0][i] = 0;
        }
        root[0] = 0;
    }

    // 核心操作：克隆节点（这是持久化的精髓，复用未修改的分支，仅复制当前节点信息）
    int clone(int p) {
        int q = ++tot;
        cnt[q] = cnt[p] + 1; // 经过当前节点的元素个数 +1
        for (int i = 0; i < SIGMA; ++i) {
            ch[q][i] = ch[p][i];
        }
        return q;
    }

    // 插入操作：从前一个版本 p_root 继承，插入 val，返回新版本的根节点编号
    int insert(int p_root, int val) {
        int q_root = clone(p_root);
        int curr = q_root, p = p_root;
        
        // 如果是多路字符串 Trie，这里可以改成遍历字符串字符
        for (int i = MAX_BITS - 1; i >= 0; --i) {
            int c = (val >> i) & 1; // 多路扩展：改成字符的映射值，如 char - 'a'
            
            ch[curr][c] = clone(ch[p][c]); // 仅分配被修改路径上的新节点
            
            curr = ch[curr][c];
            p = ch[p][c];
        }
        return q_root;
    }

    // 功能扩展：查询区间 [L, R] 内与 val 异或的最大值
    // l_root 是版本 L-1 的根，r_root 是版本 R 的根
    int query_max_xor(int l_root, int r_root, int val) {
        int res = 0;
        int p = l_root, q = r_root;
        
        for (int i = MAX_BITS - 1; i >= 0; --i) {
            int c = (val >> i) & 1;
            int best = c ^ 1; // 贪心策略：最大异或值期望走相反的位
            
            // 利用前缀和思想，cnt[q] - cnt[p] > 0 说明在这两个版本的增量中，该分支存在元素
            if (cnt[ch[q][best]] - cnt[ch[p][best]] > 0) {
                res |= (1 << i);
                q = ch[q][best];
                p = ch[p][best];
            } else {
                // 如果相反分支不存在，只能被迫走相同分支
                q = ch[q][c];
                p = ch[p][c];
            }
        }
        return res;
    }

    // 功能扩展：查询区间 [L, R] 内与 val 异或的最小值
    int query_min_xor(int l_root, int r_root, int val) {
        int res = 0;
        int p = l_root, q = r_root;
        
        for (int i = MAX_BITS - 1; i >= 0; --i) {
            int c = (val >> i) & 1;
            int best = c; // 贪心策略：最小异或值期望走相同的位
            
            if (cnt[ch[q][best]] - cnt[ch[p][best]] > 0) {
                q = ch[q][best];
                p = ch[p][best];
            } else {
                res |= (1 << i);
                q = ch[q][best ^ 1];
                p = ch[p][best ^ 1];
            }
        }
        return res;
    }
} ptrie;