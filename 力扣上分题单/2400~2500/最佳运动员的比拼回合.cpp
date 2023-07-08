// 贪心神题
class Solution {

    inline void simplify(int n, int &firstPlayer, int &secondPlayer) {
        if(firstPlayer > secondPlayer) swap(firstPlayer, secondPlayer);
        if(firstPlayer > n - secondPlayer + 1) {
            int t = n - secondPlayer + 1;
            secondPlayer = n - firstPlayer + 1;
            firstPlayer = t;
        }
    }

    int greedyMin(int n, int firstPlayer, int secondPlayer) {

        int r = (n + 1) >> 1;
        if(secondPlayer > r) {
            if((firstPlayer & 1) || (n != secondPlayer + firstPlayer)) {
                return 2;
            }
            if(!(n & 1)  && secondPlayer == r + 1) {
                return ceil(log(n) / log(2)); 
            }
            return 3;
        }
        
        int ans = ceil(log(n / (firstPlayer + secondPlayer - 1)) / log(2));

        if(n & ((1 << ans) - 1)) {
            n = (n >> ans) + 1;
        } else{
            n = (n >> ans);
        }
        
        if(firstPlayer + secondPlayer <= n) {
            ++ans;
            n = (n + 1) >> 1;
        }
        
        if(secondPlayer - firstPlayer == 1 && (n & 1)) {
            ans += log((n - 1) ^ (n - 2)) / log(2);
        }
        return ans + 1;
    }

    inline int greedyMax(int n, int firstPlayer, int secondPlayer) {
        return min((int)ceil(log(n) / log(2)), n - secondPlayer + 1);
    }

public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        simplify(n, firstPlayer, secondPlayer);
        if(firstPlayer == n - secondPlayer + 1) return {1, 1};

        return {greedyMin(n ,firstPlayer, secondPlayer), greedyMax(n ,firstPlayer, secondPlayer)};
    }
};

