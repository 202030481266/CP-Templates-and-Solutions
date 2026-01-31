class Solution {
public:
    string categorizeBox(int length, int width, int height, int mass) {
        bool is_heavy = (mass >= 100);
        bool is_bulky = (length >= 10000) || (width >= 10000) || (height >= 10000);
        long long temp = 1ll * length * width * height;
        is_bulky = is_bulky || (temp >= 1000000000);
        if (is_heavy && is_bulky) return "Both";
        else if (is_bulky) return "Bulky";
        else if (is_heavy) return "Heavy";
        else return "Neither";
    }
};