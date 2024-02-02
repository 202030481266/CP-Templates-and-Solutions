// Author: xiaoshulin
// Date  : 2024-01-24

// 最基础的基类 BaseUnionFind 提供了最基础的接口
template<uint32_t MAX_NODE = 1 << 22>
class BaseUnionFind {
private:
	static uint32_t u_father_buffer[MAX_NODE], u_size_buffer[MAX_NODE];  // 类静态变量
	static uint32_t u_buffer_use;
public:
	uint32_t* father, * size;
	uint32_t u_size, u_group_cnt;

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
	static uint32_t w_buffer_use;
public:
	T* weight;
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
		
		// 多个数组的时候可以选择在这里分配
		// 大部分情况下无需改动太多代码
		weight = w_buffer + w_buffer_use;
		w_buffer_use += n;

		// 初始化
		for (uint32_t i = 0; i < this->u_size; ++i) weight[i] = i + 1;
	}
	/*
		自定义的并查集的秩合并函数
		只需要写多一个compare函数即可，比如依据权值合并
		void merge_by_weight(uint32_t a, uint32_t b) {
			assert(0 <= a && a < u_size);
			assert(0 <= b && b < u_size);
			uint32_t fa = this->find(a), fb = this->find(b);
			if (weight[fa] > weight[fb]) std::swap(fa, fb);
			this->merge(fa, fb);
		}
	*/
	void Merge(uint32_t a, uint32_t b) {
		assert(0 <= a && a < this->u_size);
		assert(0 <= b && b < this->u_size);
		weight[a] = weight[b];
		this->merge_by_id(a, b);
	}
};
template<typename T, uint32_t MAX_NODE>
T MyUnionFind<T, MAX_NODE>::w_buffer[MAX_NODE];
template<typename T, uint32_t MAX_NODE>
uint32_t MyUnionFind<T, MAX_NODE>::w_buffer_use;


// DisUnionFind是一个带权并查集的一种常用实现，主要关注距离数组的更新即可
template<typename T, uint32_t MAX_NODE>
class DisUnionFind : public BaseUnionFind<MAX_NODE> {
private:
    static T dis_buffer[MAX_NODE];
    static uint32_t dis_buffer_use;
public:
    T* dis; // 节点到祖宗的距离
    DisUnionFind() : BaseUnionFind<MAX_NODE>() {
        resize_dis(0);
    }
    DisUnionFind(uint32_t n) : BaseUnionFind<MAX_NODE>(n) {
        resize_dis(n);
    }
    DisUnionFind(int n) : BaseUnionFind<MAX_NODE>(n) {
        assert(n >= 0);
        resize_dis((uint32_t)n);
    }
    // 初始化一个dis矩阵
    void resize_dis(uint32_t n) {
        assert(n < MAX_NODE - dis_buffer_use);
        dis = dis_buffer + dis_buffer_use;
        dis_buffer_use += n;
        
        // 初始化的代码，灵活修改
        for (uint32_t i = 0; i < n; ++i) dis[i] = 0;
    }
    uint32_t find(uint32_t i) {
        assert(0 <= i && i < this->u_size);
        if (this->father[i] != i) {
            uint32_t fa = find(this->father[i]);
            // 这里需要重载之前的find路径压缩函数
            /*
                会涉及到距离更新，更新在这里写
            */
            dis[i] += dis[this->father[i]];
            this->father[i] = fa;
        }
        return this->father[i];
    }

    // 重载按秩合并，因为需要修改权值
    bool merge_by_size(uint32_t a, uint32_t b, T d) {
        assert(0 <= a && a < this->u_size);
        assert(0 <= b && b < this->u_size);
        uint32_t fa = find(a), fb = find(b);
        if (fa == fb) return false;
        /*
            会涉及到距离更新，更新在这里写
            一定要注意很多时候合并是有方向性的！比如食物链
        */
        dis[fa] = d + dis[b] - dis[a]; // 平行四边形
        this->merge(fa, fb);
        return true;
    }
    bool merge_by_id(uint32_t a, uint32_t b, T d) {
        assert(0 <= a && a < this->u_size);
        assert(0 <= b && b < this->u_size);
        uint32_t fa = find(a), fb = find(b);
        if (fa == fb) return false;
        if (fa > fb) {
            std::swap(fa, fb);
            std::swap(a, b);
        }
        /*
		    会涉及到距离更新，更新在这里写
		    一定要注意很多时候合并是有方向性的！比如食物链
	   */
        dis[fa] = d + dis[b] - dis[a]; // 平行四边形
        this->merge(fa, fb);
        return true;
    }
};
template<typename T, uint32_t MAX_NODE>
T DisUnionFind<T, MAX_NODE>::dis_buffer[MAX_NODE];
template<typename T, uint32_t MAX_NODE>
uint32_t DisUnionFind<T, MAX_NODE>::dis_buffer_use;