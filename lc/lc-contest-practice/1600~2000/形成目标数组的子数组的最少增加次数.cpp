// 精妙的贪心构造题目
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        long long a = 0, b = 0; 

        int flag = 1;

        for (int i = 0; i < n; ++i) {
            if (i == n - 1) {
                if (flag) a += target[i];
            }
            else {
                if (target[i + 1] > target[i]) {
                    if (flag) continue;
                    else b += target[i], flag = 1;
                }
                else {
                    if (flag) {
                        a += target[i];
                        flag = 0;
                    }
                }
            }
            // cout << a << ' ' << b << endl;
        }
        return a - b;
    }
};