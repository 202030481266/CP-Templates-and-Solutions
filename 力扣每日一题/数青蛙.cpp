// 优先队列模拟
class Solution {
    typedef pair<int, int> pii;
public:
    int minNumberOfFrogs(string s) {
        int n = s.size();
        vector<int> pos[5];
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'c') pos[0].emplace_back(i);
            else if (s[i] == 'r') pos[1].emplace_back(i);
            else if (s[i] == 'o') pos[2].emplace_back(i);
            else if (s[i] == 'a') pos[3].emplace_back(i);
            else if (s[i] == 'k') pos[4].emplace_back(i);
        }
        int cc = pos[0].size(), cr = pos[1].size(), co = pos[2].size(), ca = pos[3].size(), ck = pos[4].size();
        if (cc != cr || cc != co || cc != ca || cc != ck) return -1;
        for (int i = 0; i < cc; ++i) 
            if (pos[0][i] > pos[1][i] || pos[1][i] > pos[2][i] || pos[2][i] > pos[3][i] || pos[3][i] > pos[4][i])
                return -1; // 按照升序排列
        // 合并组
        priority_queue<int, vector<int>, greater<int>> q;
        int ans = 0, cur = 0;
        for (int i = 0; i < cc; ++i) {
            while (!q.empty() && q.top() < pos[0][i]) {
                q.pop();
                ++cur; // 增加可用的青蛙
            }
            if (cur == 0) ++ans;
            else --cur;
            q.emplace(pos[4][i]);
        }
        return ans;
    }
};


// 哈希表模拟
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        // 预处理每个字母在 "croak" 中的上一个字母
        char PREVIOUS['s']; // 's' 保证 "croak" 中的任意字符都不会越界
        const string croak = "croakc";
        for (int i = 1; i < croak.length(); i++)
            PREVIOUS[croak[i]] = croak[i - 1];

        int cnt['s']{}; // 初始化
        for (char ch: croakOfFrogs) {
            char pre = PREVIOUS[ch]; // pre 为 ch 在 "croak" 中的上一个字母
            if (cnt[pre]) // 如果有青蛙发出了 pre 的声音
                cnt[pre]--; // 复用一只
            else if (ch != 'c') // 否则青蛙必须从 'c' 开始蛙鸣
                return -1; // 不符合要求
            cnt[ch]++; // 发出了 ch 的声音
        }
        if (cnt['c'] || cnt['r'] || cnt['o'] || cnt['a'])
            return -1; // 有发出其它声音的青蛙，不符合要求
        return cnt['k']; // 最后青蛙们都发出了 'k' 的声音
    }
};

