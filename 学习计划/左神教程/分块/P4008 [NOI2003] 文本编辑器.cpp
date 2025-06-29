// 相比于实现困难的块状链表，rope不失为更好的一种方法
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_cxx;

static constexpr int maxn = 3e6 + 7;

rope<char> r;
char s[maxn];
char op[20];

int main() {
    int t;
    cin >> t;
    int cursor = 0, len;
    while (t--) {
        scanf("%s", op);
        if (op[0] == 'I') {
            scanf("%d", &len);
            s[len] = '\0';
            for (int i = 0; i < len; ++i) {
                s[i] = '\0';
                while(s[i] < 32 || 126 < s[i])
                    s[i] = getchar();
            }
            r.insert(cursor, s, len);
        }
        else if (op[0] == 'M') {
            scanf("%d", &cursor);
        }
        else if (op[0] == 'D') {
            scanf("%d", &len);
            r.erase(cursor, len);
        }
        else if (op[0] == 'G') {
            scanf("%d", &len);
            for (int i = cursor; i < cursor + len; ++i) putchar(r[i]);
            puts("");
        }
        else if (op[0] == 'P') {
            --cursor;
        }
        else {
            ++cursor;
        }
    }
}