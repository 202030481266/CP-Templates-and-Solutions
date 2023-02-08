// https://leetcode.cn/problems/ipo/
// 贪心技巧： 在每一次选择利润最高的可以做的项目

class Solution {
public:
    struct Node {
        int c, p;
        Node() {}
        Node(int _c, int _p): c(_c), p(_p) {}
        bool operator < (const Node &rhs) const {
            return c < rhs.c;
        };
    };
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<Node> a;
        priority_queue<int, vector<int>, less<int>> q;

        for (int i = 0; i < n; i++) {
            a.emplace_back(Node(capital[i], profits[i]));
        }
        sort(a.begin(), a.end());
        // for (auto rhs : a) {
        //     cout << rhs.c << ' ' << rhs.p << endl;
        // }
        int l = 0, ans = 0;
        while (k) {
            while (l < n && a[l].c <= w) q.push(a[l++].p);
            if (q.empty()) break;
            else {
                // cout << "k : " << k << ' ' << q.top() << endl;
                w += q.top();
                q.pop();
                --k;
            }
        }
        return w;
    }
};