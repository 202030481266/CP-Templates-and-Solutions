typedef pair<int, int> pii;
class StockSpanner {
    stack<pii> s;
public:
    StockSpanner() {
    }

    int next(int price) {
        int res = 1;
        while (!s.empty() && price >= s.top().first) {
            res += s.top().second;
            s.pop();
        }
        s.emplace(price, res);
        return res;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */