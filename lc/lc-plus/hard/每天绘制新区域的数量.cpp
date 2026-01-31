// 最基础的基类 BaseUnionFind 提供了最基础的接口
template<uint32_t MAX_NODE = 1 << 22>
class BaseUnionFind {
private:
    static uint32_t u_father_buffer[MAX_NODE], u_size_buffer[MAX_NODE];  // 类静态变量
public:
    uint32_t* father, * size;
    uint32_t u_size, u_group_cnt;
    static uint32_t u_buffer_use;
    BaseUnionFind() { resize(0); }
    BaseUnionFind(uint32_t n) { resize(n); }
    BaseUnionFind(int n) {
        assert(n >= 0);
        resize((uint32_t)n);
    }
    // resize 函数，一般用来初始化
    void resize(uint32_t n) {
        // 索引规定W为[0, n - 1]
        assert(n < MAX_NODE - u_buffer_use); // 检查大小
        u_size = n;
        u_group_cnt = n;
        if (n == 0) return;
        father = u_father_buffer + u_buffer_use;
        size = u_size_buffer + u_buffer_use;
        u_buffer_use += n;
        for (uint32_t i = 0; i < n; ++i) {
            father[i] = i;
            size[i] = 1;
        }
    }
    // 路径压缩，是一种two-process method，向上查找祖先，向下返回更新
    uint32_t find(uint32_t i) {
        assert(0 <= i && i < u_size);
        return father[i] == i ? i : father[i] = find(father[i]);
    }

    // 获取i所在的集合的大小
    uint32_t get_group_size(uint32_t i) {
        assert(0 <= i && i < u_size); 
        return size[find(i)];
    }

    // 合并parent_a和parent_b所在的集合
    // parent_a是a集合的祖先，parent_b是b集合的祖先
    void merge(uint32_t fa, uint32_t fb) {
        assert(0 <= fa && fa < u_size);
        assert(0 <= fb && fb < u_size);
        if (fa == fb) return;
        father[fa] = fb;
        size[fb] += size[fa];
        --u_group_cnt;
    }

    // 合并集合（按秩合并，秩为集合大小）
    bool merge_by_size(uint32_t a, uint32_t b) {
        assert(0 <= a && a < u_size);
        assert(0 <= b && b < u_size);
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] > size[b]) std::swap(a, b);
        merge(a, b); // a -> b, small -> big
        return true;
    }

    // 合并集合 （按秩合并，秩为ID大小）
    bool merge_by_id(uint32_t a, uint32_t b) {
        assert(0 <= a && a < u_size);
        assert(0 <= b && b < u_size);
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (a > b) std::swap(a, b);
        merge(a, b); // a -> b, small -> big
        return true;
    }

    // 判断a和b是否在同一个集合里面
    bool in_same_group(uint32_t a, uint32_t b) {
        assert(0 <= a && a < u_size);
        assert(0 <= b && b < u_size);
        return find(a) == find(b);
    }

    // 集合的祖先
    std::vector<uint32_t> parents() {
        std::vector<uint32_t> res;
        res.reserve(u_group_cnt);
        for (uint32_t i = 0; i < u_size; ++i) {
            if (i == father[i]) res.push_back(i);
        }
        return res;
    }

    // 集合分组
    std::vector<std::vector<uint32_t>> groups() {
        std::vector<std::vector<uint32_t>> res(u_size);
        std::vector<uint32_t> index(u_size);
        // 记录这些对应的祖先编号
        for (uint32_t i = 0, j = 0; i < u_size; ++i) {
            if (i == father[i]) {
                res[j].reserve(size[i]);
                index[i] = j++;
            }
        }
        // [0, j)
        for (uint32_t i = 0; i < u_size; ++i) {
            res[index[find(i)]].push_back(i);
        }
        return res;
    }
};
// 输出集合parent的信息
template<typename Ostream, uint32_t MAX_NODE = 1 << 22>
Ostream& operator<<(Ostream& out, const BaseUnionFind<MAX_NODE>& un) {
    out << "[";
    for (uint32_t i = 0; i < un.u_size; ++i) {
        if (i) out << ", ";
        out << un.father[i];
    }
    out << "]";
    return out;
}
// 输出集合groups的信息
template<typename Ostream>
Ostream& operator<<(Ostream& out, const std::vector<std::vector<uint32_t>>& groups) {
    out << "[";
    for (uint32_t i = 0; i < groups.size(); ++i) {
        if (i) out << ", ";
        out << "[";
        for (uint32_t j = 0; j < groups[i].size(); ++j) {
            if (j) out << ", ";
            out << groups[i][j];
        }
        out << "]";
    }
    out << "]";
    return out;
}
// 显式声明
template<uint32_t MAX_NODE>
uint32_t BaseUnionFind<MAX_NODE>::u_father_buffer[MAX_NODE];
template<uint32_t MAX_NODE>
uint32_t BaseUnionFind<MAX_NODE>::u_size_buffer[MAX_NODE];
template<uint32_t MAX_NODE>
uint32_t BaseUnionFind<MAX_NODE>::u_buffer_use;
// BaseUnionFind的派生类，可以自定义自己的权重数组，然后修改Merge函数以及初始化
template<typename T, uint32_t MAX_NODE>
class MyUnionFind : public BaseUnionFind<MAX_NODE> {
private: 
    static T w_buffer[MAX_NODE];
public:
    T* nxt, *vis;
    static uint32_t w_buffer_use;
    MyUnionFind() : BaseUnionFind<MAX_NODE>() { 
        resize_weight(0);
    }
    MyUnionFind(uint32_t n) : BaseUnionFind<MAX_NODE>(n) {
        resize_weight(n); 
    }
    MyUnionFind(int n) : BaseUnionFind<MAX_NODE>(n) {
        assert(n >= 0);
        resize_weight((uint32_t)n); 
    }

    // 初始化参数
    void resize_weight(uint32_t n) {
        assert(n < MAX_NODE - w_buffer_use);
        if (n == 0) return;
        
        // 开了两个数组
        nxt = w_buffer + w_buffer_use;
        w_buffer_use += n;
        vis = w_buffer + w_buffer_use;
        w_buffer_use += n;

        // 初始化
        // 表示下一个没有被合并的点
        for (uint32_t i = 0; i < n; ++i) {
            nxt[i] = i + 1;
            vis[i] = 0;
        }
    }
    int Merge(uint32_t a, uint32_t b) {
        assert(0 <= a && a < this->u_size);
        assert(0 <= b && b < this->u_size);
        uint32_t fb = this->find(b);
        int res = 0;
        while (a <= b) { // merge区间[a,b]
            if (!vis[a]) {
                ++res;
                vis[a] = 1;
            }
            int tmp = nxt[a];
            this->father[a] = fb;
            nxt[a] = nxt[b];
            a = tmp;
        }
        return res;
    }
};
template<typename T, uint32_t MAX_NODE>
T MyUnionFind<T, MAX_NODE>::w_buffer[MAX_NODE];
template<typename T, uint32_t MAX_NODE>
uint32_t MyUnionFind<T, MAX_NODE>::w_buffer_use;

MyUnionFind<int, 1000000> un(100000);

class Solution {
public:
    vector<int> amountPainted(vector<vector<int>>& paint) {
        int mx = 0, n = paint.size();
        for (auto& e : paint) 
            mx = max(mx, e[1]);
        // init
        un.w_buffer_use = 0;
        un.u_buffer_use = 0;
        un.resize(mx + 1);
        un.resize_weight(mx + 1);
        vector<int> ans;
        for (auto& e : paint) {
            int l = e[0], r = e[1] - 1;
            ans.push_back(un.Merge(l, r));
        }
        return ans;
    }
};