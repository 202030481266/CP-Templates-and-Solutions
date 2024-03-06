class Solution {
public:
    bool findGameWinner(int n) {
        int sg1 = 0, sg2 = 1;
        for (int i = 1;i < n;++i) {
            const int t = (sg1 + 1) ^ (sg2 + 1);
            sg2 = sg1;
            sg1 = t;
        }
        return sg1 != 0;
    }
};

