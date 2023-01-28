// LFU缓存设计在LRU的基础上难度大了很多，主要是要维护一个使用次数
// LRU的设计技巧主要在于使用哈希表和双向链表来快速定位和插入删除


class LRUCache {
private: 
	int cap;
	list<pair<int, int>> lst; // [key, value]
	unordered_map<int, list<pair<int, int>>::iterator> key_map; // [key, pointer]
public:
    LRUCache(int capacity) {
    	this->cap = capacity;
    	lst.clear();
    	key_map.clear();
    }
    
    int get(int key) {
    	if (key_map.count(key)) {
    		auto cur = key_map[key];
    		int value = cur->second;
    		key_map[key] = lst.emplace(lst.end(), key, value);
    		lst.erase(cur);
    		return value;
    	}
    	return -1;
    }
    
    void put(int key, int value) {
    	if (key_map.count(key)) {
    		auto cur = key_map[key];
    		key_map[key] = lst.emplace(lst.end(), key, value);
    		lst.erase(cur);
    	} else {
    		if (cap > 0) {
    			key_map[key] = lst.emplace(lst.end(), key, value);
    			--cap;
    		} else {
    			auto cur = lst.begin();
    			key_map.erase(cur->first);
    			lst.erase(cur);
    			key_map[key] = lst.emplace(lst.end(), key, value);
    		}
    	}
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


// 考虑到全O(1)数据结构中的次数维护技巧，使用桶排序来进行维护LFU
// 但是为了能够快速删除和插入，还要在桶内设置一个双链表和哈希表，相当于维护一个队列

struct Node {
	int key, val, times;
	Node() { key = val = times = 0; }
	Node(int _k, int _v, int _t): key(_k), val(_v), times(_t) {}
};
class LFUCache {
private:
	// 一定要开全局变量，否则会出现错误
	int minn, cap;
	unordered_map<int, list<Node>::iterator> key_map;
	unordered_map<int, list<Node>> time_map;
public:
    LFUCache(int capacity) {
    	cap = capacity;
    	minn = 0;
    	key_map.clear();
    	time_map.clear();
    }
    
    int get(int key) {
    	if (cap == 0) return -1;
    	auto it = key_map.find(key);
    	if (it == key_map.end()) {
    		// means no value
    		return -1;
    	}
    	auto cur = key_map[key];
    	int freq = cur->times, value = cur->val;
    	time_map[freq].erase(cur);
    	if (time_map[freq].empty()) {
    		if (minn == freq) ++minn;
    		time_map.erase(freq);
    	}
    	time_map[freq + 1].emplace_front(Node(key, value, freq + 1));
    	key_map[key] = time_map[freq + 1].begin();
    	return value;
    }
    
    void put(int key, int value) {
    	if (cap == 0) return;
    	auto it = key_map.find(key);
    	if (it == key_map.end()) {
    		// no such key
    		if (key_map.size() == cap) {
    			// need delete one element
    			auto cur = time_map[minn].back();
    			key_map.erase(cur.key);
    			time_map[minn].pop_back();
    			if (time_map[minn].empty()) {
    				time_map.erase(minn);
    			}
    		}
    		time_map[1].emplace_front(Node(key, value, 1));
    		key_map[key] = time_map[1].begin();
    		minn = 1;
    	} else {
    		// update the value
    		auto cur = key_map[key];
    		int freq = cur->times;
    		time_map[freq].erase(cur);
    		if (time_map[freq].empty()) {
    			if (minn == freq) ++minn;
    			time_map.erase(freq);
    		}
    		time_map[freq + 1].emplace_front(Node(key, value, freq + 1));
    		key_map[key] = time_map[freq + 1].begin();
    	}
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */