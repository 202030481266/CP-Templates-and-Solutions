#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class TicTacToe {
public:
    vector<int> row[2],col[2],diag[2];
    int n;
    TicTacToe(int n) {
        row[0].resize(n);
        row[1].resize(n);
        col[0].resize(n);
        col[1].resize(n);
        diag[0].resize(2);
        diag[1].resize(2);
        this->n = n;
    }
    
    int move(int r, int c, int player) {
        --player;
        row[player][r]++;
        col[player][c]++;
        if (r==c) diag[player][0]++;
        if (r+c==row[player].size()-1) diag[player][1]++;
        if (row[player][r]==n || col[player][c]==n || diag[player][0]==n || diag[player][1]==n) 
            return player+1;
        return 0;
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */