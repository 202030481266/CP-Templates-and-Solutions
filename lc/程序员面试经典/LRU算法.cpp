// 手写链表
struct Node {
    int key, value;
    Node *prev, *next;
    Node(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
    Node(): prev(nullptr), next(nullptr) {}
};
class LRUCache {
    Node* tail, *head;
    unordered_map<int, Node*> cache;
    int siz = 0, cap = 0;
public:
    LRUCache(int capacity) {
        cap = capacity;
        // 哨兵节点
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    void moveToHead(Node* cur) {
        cur->next = head->next;
        cur->prev = head;
        head->next->prev = cur;
        head->next = cur;
    }
    
    void removeNode(Node* cur) {
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;
    }
    
    int get(int key) {
        if (!cache.count(key)) return -1;
        Node* cur = cache[key];
        removeNode(cur);
        moveToHead(cur);
        return cur->value;
    }

    void removeTail() {
        Node* cur = tail->prev;
        cache.erase(cur->key);
        removeNode(cur);
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            Node* cur = new Node(key, value);
            cache[key] = cur;
            moveToHead(cur);
            ++siz;
            if (siz > cap) {
                removeTail();
            }
        }
        Node* cur = new Node(key, value);
        removeNode(cache[key]);
        moveToHead(cur);
        cache[key] = cur;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */