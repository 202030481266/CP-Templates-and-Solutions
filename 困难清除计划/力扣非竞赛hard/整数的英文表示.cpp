// 又是恶心的模拟题目
class Solution {
    unordered_map<int, string> special;
public:
    string dfs(int num) {
        if (0 <= num && num <= 99) return special[num];
        int billion = 1000000000, million = 1000000, thousand = 1000, hundred = 100;
        int B = num / billion;
        int M = (num % billion) / million;
        int T = (num % million) / thousand;
        int H = (num % thousand) / hundred;
        int rem = num % hundred; 
        vector<string> res;
        if (B) res.push_back(dfs(B) + " " + "Billion");
        if (M) res.push_back(dfs(M) + " " + "Million");
        if (T) res.push_back(dfs(T) + " " + "Thousand");
        if (H) res.push_back(dfs(H) + " " + "Hundred");
        if (rem) res.push_back(dfs(rem));
        string ans;
        for (int i = 0; i < res.size(); ++i) {
            ans += res[i];
            if (i < res.size() - 1) ans.push_back(' ');
        }
        return ans;
    }
    string numberToWords(int num) {
        vector<string> numbers {
            "Zero",
            "One",
            "Two",
            "Three",
            "Four",
            "Five",
            "Six",
            "Seven",
            "Eight",
            "Nine",
            "Ten",
            "Eleven",
            "Twelve",
            "Thirteen",
            "Fourteen",
            "Fifteen",
            "Sixteen",
            "Seventeen",
            "Eighteen",
            "Nineteen",
            "Twenty"
        };
        for (int i = 0; i <= 20; ++i)
            special[i] = numbers[i];
        special[20] = "Twenty";
        special[30] = "Thirty";
        special[40] = "Forty";
        special[50] = "Fifty";
        special[60] = "Sixty";
        special[70] = "Seventy";
        special[80] = "Eighty";
        special[90] = "Ninety";
        for (int i = 21; i <= 99; ++i) {
            if (!special.count(i)) {
                int k = (i / 10) * 10, r = i % 10;
                special[i] = special[k] + " " + special[r];
            }
        }
        return dfs(num);
    }
};