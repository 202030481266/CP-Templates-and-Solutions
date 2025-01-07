// 动态规划
constexpr int BIAS = 1000;
char f[41][41][BIAS*2];
inline bool isa(char c) { return 'a' <= c && c <= 'z';}
const char *A, *B;
int la, lb;
char dfs(int i, int j, int d) {
    char& res = f[i][j][d];
    if (res != -1) return res;
    if (i == la && j == lb) 
        return res = (d == BIAS); // d == 0
    res = 0;
    if (d == BIAS && i < la && j < lb && isa(A[i]) && isa(B[j])) 
        return res = (A[i] != B[j] ? 0 : dfs(i+1, j+1, BIAS));
    if (d <= BIAS && i < la) {
        if (!isa(A[i])) {
            for (int p = i, v = 0; p < la && !isa(A[p]); p++) {
                v = v * 10 + A[p] - '0';
                if (dfs(p+1, j, d+v))
                    return res = 1;
            }
        } else if (d < BIAS && dfs(i+1, j, d+1)) {
            return res = 1;
        }
    }
    if (d >= BIAS && j < lb) {
        if (!isa(B[j])) {
            for (int p = j, v = 0; p < lb && !isa(B[p]); p++) {
                v = v*10 + B[p]-'0';
                if (dfs(i, p+1, d-v))
                    return res = 1;
            }
        } else if (d > BIAS && dfs(i, j+1, d-1)) {
            return res = 1;
        }
    }
    return res;
}

class Solution {
public:
    bool possiblyEquals(string s1, string s2) {
        A = &s1[0]; B = &s2[0];
        la = s1.size(); lb = s2.size();
        memset(f, -1, sizeof f);
        return dfs(0, 0, BIAS);
    }
};