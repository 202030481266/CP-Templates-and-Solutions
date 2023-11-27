class FrontMiddleBackQueue {
    list<int> L;
public:
    FrontMiddleBackQueue() {
    }
    
    void pushFront(int val) {
        L.push_front(val);
    }
    
    void pushMiddle(int val) {
        auto it = L.begin();
        advance(it, L.size() / 2);
        L.insert(it, val);
    }
    
    void pushBack(int val) {
        L.push_back(val);
    }
    
    int popFront() {
        if (L.empty()) return -1;
        int ans = L.front();
        L.pop_front();
        return ans;
    }
    
    int popMiddle() {
        if (L.empty()) return -1;
        auto it = L.begin();
        advance(it, (L.size() - 1) / 2);
        int ans = *it;
        L.erase(it);
        return ans;
    }
    
    int popBack() {
        if (L.empty()) return -1;
        int ans = L.back();
        L.pop_back();
        return ans;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */