class Solution {
public:
    int isWinner(vector<int>& player1, vector<int>& player2) {
        int a = 0, b = 0, n = player1.size();
        for (int i = 0; i < n; ++i) {
            bool flag = false;
            if (i > 0) flag = flag || (player1[i - 1] == 10);
            if (i > 1) flag = flag || (player1[i - 2] == 10);
            a += (flag ? player1[i] * 2 : player1[i]);
        }
        for (int i = 0; i < n; ++i) {
            bool flag = false;
            if (i > 0) flag = flag || (player2[i - 1] == 10);
            if (i > 1) flag = flag || (player2[i - 2] == 10);
            b += (flag ? player2[i] * 2 : player2[i]);
        }
        if (a > b) return 1;
        if (b > a) return 2;
        return 0;
    }
};