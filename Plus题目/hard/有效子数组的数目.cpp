template<typename T, uint32_t MAX_NODE = 1 << 22>
struct Stack {
    static T st[MAX_NODE];
    static uint32_t st_buffer_use;
    uint32_t p;

    Stack():p(0) {}
    Stack(int n) {
        st_buffer_use = (uint32_t)n;
        p = 0;
    } 
    Stack(uint32_t n) {
        st_buffer_use = n;
        p = 0;
    }
    void push(T x) { st[p++] = x; }
    void pop() { --p; }
    T top() { return st[p - 1]; }
    uint32_t size() { return p; }
    bool empty() { return p == 0; }
    void clear() { p = st_buffer_use = 0; }
};
template<typename T, uint32_t MAX_NODE>
T Stack<T, MAX_NODE>::st[MAX_NODE];
template<typename T, uint32_t MAX_NODE>
uint32_t Stack<T, MAX_NODE>::st_buffer_use;

class Solution {
public:
    int validSubarrays(vector<int>& nums) {
        // 单调栈
        Stack<int> s;
        int ans = 0, n = nums.size();
        for (int i = 0; i < nums.size(); ++i) {
            while (!s.empty() && nums[s.top()] > nums[i]) {
                // [s.top(), i)
                ans += (i - s.top());
                s.pop();
            }
        }
        while (!s.empty()) {
            ans += (n - s.top());
            s.pop();
        }
        return ans;
    }
};