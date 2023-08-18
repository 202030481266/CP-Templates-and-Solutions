class Solution {
    int memory[8][1 << 8];
    vector<int> compressed_seats;
    int f(int X, int row_num, int width) {
        if (memory[row_num][X] != -1)
            return memory[row_num][X];
        int ans = 0;
        for (int scheme = 0; scheme != (1 << width); ++scheme) {
            if (scheme & ~X || scheme & (scheme << 1))
                continue;
            int curans = 0;
            for (int j = 0; j != width; ++j)
                if ((1 << j) & scheme)
                    ++curans;
            if (row_num == compressed_seats.size() - 1)
                ans = max(ans, curans);
            else {
                int next_seats = compressed_seats[row_num + 1];
                next_seats &= ~(scheme << 1);
                next_seats &= ~(scheme >> 1);
                ans = max(ans, curans + f(next_seats, row_num + 1, width));
            }
        }
        memory[row_num][X] = ans;
        return ans;
    }
    
    int compress(vector<char>& row) {
        int ans = 0;
        for (char c : row) {
            ans <<= 1;
            if (c == '.')
                ++ans;
        }
        return ans;
    }

public:
    int maxStudents(vector<vector<char>>& seats) {
        for (int i = 0; i != seats.size(); ++i)
            for (int j = 0; j != (1 << seats[0].size()); ++j)
                memory[i][j] = -1;
        for (auto row: seats)
            compressed_seats.push_back(compress(row));
        return f(compressed_seats[0], 0, seats[0].size());
    }
};