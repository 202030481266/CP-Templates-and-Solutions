class MaxStack {
    // 实际上可以使用时间戳来管理栈
public:
    set<pair<int, int>> s;
    set<pair<int, int>> mx;
    // unordered_map<int, vector<int>> buck;

    int time = 0;

    MaxStack() {
        
    }
    
    void push(int x) {
        s.emplace(time, x);
        mx.emplace(x, time);
        ++time;
    }
    
    int pop() {
        int x = s.rbegin()->second, t = s.rbegin()->first;
        s.erase(prev(s.end()));
        mx.erase(mx.find(make_pair(x, t)));
        return x;
    }
    
    int top() {
        return s.rbegin()->second;
    }
    
    int peekMax() {
        return mx.rbegin()->first;
    }
    
    int popMax() {
        int x = mx.rbegin()->first, t = mx.rbegin()->second;
        mx.erase(prev(mx.end()));
        s.erase(s.find(make_pair(t, x)));
        return x;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */