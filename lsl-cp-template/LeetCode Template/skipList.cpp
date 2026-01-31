constexpr int MAX_LEVEL = 32;
constexpr double P_FACTOR = 0.25;

// 一种非常优秀的数据结构

struct SkiplistNode {
    // skiplist的节点代表的是一个val在max_level层链表中每一层的指针
    // 每一个节点的高度层数是不一样的
    int val;
    vector<SkiplistNode*> forward;  // 表示的是层数
    SkiplistNode() {}
    SkiplistNode(int _val, int _maxlevel = MAX_LEVEL):
        val(_val), forward(_maxlevel, nullptr) {}
};
class Skiplist {
public:
    SkiplistNode* head;
    int level;
    // 梅森素数旋转算法构造随机数
    mt19937 gen{random_device{}()};
    uniform_real_distribution<double> dis;

    Skiplist(): head(new SkiplistNode(-1)), level(0), dis(0, 1) {}
    
    bool search(int target) {
        auto cur = this->head;
        // 从最大的层数开始搜索
        for (int i = level - 1; i >= 0; --i) {
            // 一直往前搜索直到下一个节点的值大于等于自己
            // 对于每一层都是一样的操作
            while (cur->forward[i] && cur->forward[i]->val < target) {
                cur = cur->forward[i];
            }
        }
        // 检查前面的值是否等于target
        cur = cur->forward[0];
        if (cur && cur->val == target) return true;
        return false;
    }
    
    void add(int num) {
        // 往上更新的层数使用随机数决定
        // 层数的控制是非常关键的，适当提升层数能够提升很大的性能
        vector<SkiplistNode*> update(MAX_LEVEL, head);
        auto cur = this->head;
        for (int i = level - 1; i >= 0; --i) {
            while (cur->forward[i] && cur->forward[i]->val < num) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        int lv = get_random();
        level = max(level, lv);  // level是节点的最大层数
        auto newNode = new SkiplistNode(num, lv);
        for (int i = 0; i < lv; ++i) {
            // 对第 i 层的状态进行更新，将当前元素的 forward 指向新的节点
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    
    bool erase(int num) {
        vector<SkiplistNode*> update(MAX_LEVEL, nullptr);
        auto cur = this->head;
        for (int i = level - 1; i >= 0; --i) {
            // 查找到最接近num的数值
            while (cur->forward[i] && cur->forward[i]->val < num) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        cur = cur->forward[0];
        if (!cur || cur->val != num) return false; // 值不存在返回false
        for (int i = 0; i < level; ++i) {
            // 没有指向就退出更新
            if (update[i]->forward[i] != cur) break;
            update[i]->forward[i] = cur->forward[i];
        }
        delete cur;
        // 更新当前的level，把一些没有用的层直接除掉
        while (level > 1 && head->forward[level - 1] == nullptr) --level;
        return true;
    }
    int get_random() {
        int lv = 1;
        while (dis(gen) < P_FACTOR && lv < MAX_LEVEL) ++lv;
        return lv;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */