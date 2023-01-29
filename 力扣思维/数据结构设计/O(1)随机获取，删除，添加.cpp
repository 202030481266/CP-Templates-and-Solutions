// allow duplicate
// 那就使用unordered_set数据结构，因为插入和删除，查找均摊都是O(1)

class RandomizedCollection {
public:
    vector<int> a;
    unordered_map<int, unordered_set<int>> hs;

    RandomizedCollection() { srand((unsigned)time(NULL)); }
    
    bool insert(int val) {
        bool res = hs.count(val) > 0 ? false : true;
        hs[val].emplace(a.size());
        a.emplace_back(val);
        return res;
    }
    
    bool remove(int val) {
        if (!hs.count(val)) return false;
        int temp = a.back();
        if (temp == val) {
            hs[val].erase(a.size() - 1);
            a.pop_back();
        } else {
            auto val_p = hs[val].begin();
            // put the last one in index
            int val_i = *val_p;  // the index of val;
            hs[val].erase(val_p);
            a[val_i] = temp;
            hs[temp].erase(a.size() - 1);
            hs[temp].emplace(val_i);
            a.pop_back();
        }
        if (hs[val].empty()) hs.erase(val);
        return true;
    }
    
    int getRandom() {
        int index = rand() % a.size();
        return a[index];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */


// 下面的是不允许重复的场景
// 技巧：vector的删除瓶颈在于查找元素和位移，使用哈希表来进行优化可以O(1)获取元素位置
// 使用vector最后面的元素来替补之前删除的元素
class RandomizedSet {
public:
    RandomizedSet() {
        srand((unsigned)time(NULL));
    }
    
    bool insert(int val) {
        if (indices.count(val)) {
            return false;
        }
        int index = nums.size();
        nums.emplace_back(val);
        indices[val] = index;
        return true;
    }
    
    bool remove(int val) {
        if (!indices.count(val)) {
            return false;
        }
        int index = indices[val];
        int last = nums.back();
        nums[index] = last;
        indices[last] = index;
        nums.pop_back();
        indices.erase(val);
        return true;
    }
    
    int getRandom() {
        int randomIndex = rand()%nums.size();
        return nums[randomIndex];
    }
private:
    vector<int> nums;
    unordered_map<int, int> indices;
};