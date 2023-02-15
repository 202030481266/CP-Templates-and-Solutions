// https://leetcode.cn/problems/online-stock-span/
// 维护单调递减的栈，那么对于x就可以寻找到左边第一个大于自己的数

class StockSpanner {
public:
    vector<int> a;
    stack<int> s;
    StockSpanner() {
        a.emplace_back(INT_MAX);
        s.push(0);
    }
    
    int next(int price) {
        a.emplace_back(price);
        while (!s.empty() && a[s.top()] <= price) 
            s.pop();
        int ans = (a.size() - s.top() - 1);
        s.push(a.size() - 1);
        return ans;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */