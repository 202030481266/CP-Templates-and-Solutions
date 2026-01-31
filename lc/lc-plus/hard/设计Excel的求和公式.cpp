// 忽略了一个关键点
// sum 公式是一个DAG，所以单纯的树状数组是无法表达一个表达式的

class Excel {
public:
    int n, m;
    vector<vector<string>> s;
    vector<vector<int>> a;
    vector<vector<int>> b;
    Excel(int height, char width) {
        n = height; 
        m = width - 'A' + 1; 
        // 0-index
        s.resize(n * m); 
        a = vector(n, vector<int>(m, 0));
        b = vector(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j) 
                s[i * m + j].push_back(encode(i + 1, (char)(j + 'A')));
    }

    string encode(int i, char j) {
        string tmp(1, j);
        return tmp + to_string(i);
    }

    pair<int, int> parse(string& str) {
        int r = 0, c = str[0] - 'A';
        for (int i = 1; i < str.size(); ++i)
            r = r * 10 + str[i] - '0';
        // cout << str << ' ' << r << ' ' << c << endl;
        return {r - 1, c};
    }
    
    void set(int row, char column, int val) {
        int c = column - 'A', r = row - 1;
        a[r][c] = val;
        b[r][c] = 0;
        s[r * m + c].clear();
        s[r * m + c].push_back(encode(row, column));
    }

    int dfs(int r, int c) {
        // cout <<r << ' ' << c << endl;
        if (!b[r][c]) return a[r][c];
        int ans = 0;
        for (string& v : s[r * m + c]) {
            int p = -1;
            for (int i = 0; i < v.size(); ++i) {
                if (v[i] == ':') {
                    p = i;
                    break;
                }
            }
            if (p == -1) {
                auto pos = parse(v);
                ans += dfs(pos.first, pos.second);
            }
            else {
                // [0, p), (p, v.size() - 1]
                string l = v.substr(0, p), r = v.substr(p + 1, v.size() - 1 - p);
                auto left = parse(l), right = parse(r);
                for (int i = left.first; i <= right.first; ++i)
                    for (int j = left.second; j <= right.second; ++j)
                        ans += dfs(i, j);
            }
        }
        return ans;
    }

    int get(int row, char column) {
        int r = row - 1, c = column - 'A';
        return dfs(r, c);
    }
    
    int sum(int row, char column, vector<string> numbers) {
        int r = row - 1, c = column - 'A';
        s[r * m + c] = numbers;
        b[r][c] = 1;
        return get(row, column);
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(height, width);
 * obj->set(row,column,val);
 * int param_2 = obj->get(row,column);
 * int param_3 = obj->sum(row,column,numbers);
 */