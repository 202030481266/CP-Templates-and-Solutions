#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

const int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; // 右下左上
unordered_map<string, int> dir = {{"R",0},{"D",1},{"L",2},{"U",3}};

class SnakeGame {
public:
    queue<pii> q;
    int n,m,d,p;
    pii head;
    vector<vector<int>> f;
    set<pii> s;
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        m = width;
        n = height;
        d = -1;// unknown
        head = {0,0};
        f = food;
        p = 0;
        s.insert(head);
        q.push(head);
    }
    
    int move(string direction) {
        d = dir[direction];
        pii nxt = {head.first+dirs[d][0],head.second+dirs[d][1]};
        if (nxt.first<0 || nxt.first>=n || nxt.second<0 || nxt.second>=m) return -1; // out of bound   
        if (p < f.size() && nxt.first == f[p][0] && nxt.second == f[p][1]) p++;
        else { 
            pii tail = q.front();
            q.pop();
            s.erase(tail);
        }
        if (s.find(nxt) != s.end()) { 
            return -1; // hit itself 
        }
        q.push(nxt);
        s.insert(nxt);
        head = nxt;
        return p;//[0,p)
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */