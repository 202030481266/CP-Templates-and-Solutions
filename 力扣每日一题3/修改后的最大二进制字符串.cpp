class Solution {
public:
    string maximumBinaryString(string binary) {
        int cnt = 0, n = binary.size(), p = -1;
        for (int i = 0; i < n; ++i) {
            if (binary[i] == '0') {
                p = i;
                break;
            }
        }
        if (p == -1) return binary; // 全是1
        for (int i = p + 1; i < n; ++i)
            if (binary[i] == '1') ++cnt;
        // [p, n)
        int rem = (n - p) - cnt;
        for (int i = p; i < p + rem - 1; ++i)
            binary[i] = '1';
        binary[p + rem - 1] = '0';
        for (int i = p + rem; i < n; ++i)
            binary[i] = '1';
        return binary;
    }
};