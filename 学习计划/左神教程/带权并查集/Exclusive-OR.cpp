#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 2e4 + 7;
int fa[maxn], dis[maxn];
int n, m, conflict = 0, step = 0;

int find(int x) {
    if (fa[x] == x) return x;
    int f = fa[x];
    fa[x] = find(fa[x]);
    dis[x] ^= dis[f];
    return fa[x];
}

bool merge(int u, int v, int w) {
    ++step;
    int fu = find(u), fv = find(v);
    if (fu == fv) {
        if ((dis[u] ^ dis[v]) != w) {
            conflict = 1;
            return false;
        }
    }
    else {
        if (fu == n) {
            swap(fu, fv);
        }
        fa[fu] = fv;
        dis[fu] = dis[u] ^ dis[v] ^ w;
    }
    return true;
}

int main() {
    string line;
    int caseNo = 1;
    cin >> n >> m;
    while (n != 0 || m != 0) {
        cout << "Case " << caseNo++ << ":\n";
        cin.ignore();
        for (int i = 0; i <= n; ++i) {
            fa[i] = i;
            dis[i] = 0;
        }
        step = 0;
        conflict = 0;
        for (int i = 1; i <= m; ++i) {
            getline(cin, line);
            if (conflict) continue;
            std::istringstream iss(line);
            vector<string> tokens;
            string token;
            while (iss >> token) {
                tokens.push_back(token);
            }
            if (tokens[0][0] == 'I') {
                if (tokens.size() == 3) {
                    // I u w
                    int u = stoi(tokens[1]), w = stoi(tokens[2]);
                    bool res = merge(u, n, w);
                    if (!res) {
                        cout << "The first " << step << " facts are conflicting." << '\n'; 
                    }
                }
                else {
                    // I u v w
                    int u = stoi(tokens[1]), v = stoi(tokens[2]), w = stoi(tokens[3]);
                    bool res = merge(u, v, w);
                    if (!res) {
                        cout << "The first " << step << " facts are conflicting." << '\n'; 
                    }
                }
            }
            else {
                vector<int> tmp;
                int ans = 0;
                for (int j = 2; j < tokens.size(); ++j) {
                    int u = stoi(tokens[j]);
                    int f = find(u);
                    ans ^= dis[u];
                    if (f != n) {
                        tmp.push_back(f);
                    }
                }
                sort(tmp.begin(), tmp.end());
                int p = 0, flag = 1;
                while (p < tmp.size() && flag) {
                    int j = p+1;
                    while (j < tmp.size() && tmp[j] == tmp[p]) ++j;
                    if ((j-p) & 1) {
                        flag = 0;
                        break;
                    }
                    p = j;
                }
                if (flag) cout << ans << '\n';
                else cout << "I don't know." << '\n';
            }
        }
        cout << '\n';
        cin >> n >> m; // 最后一个测试用例不能有空行
    }
}