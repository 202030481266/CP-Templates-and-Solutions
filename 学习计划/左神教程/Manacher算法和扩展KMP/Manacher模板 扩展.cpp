#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Manacher算法：计算所有位置的回文半径
pair<vector<int>, vector<int>> manacher(const string& s) {
    int n = s.length();
    vector<int> d1(n, 0);  // odd radii
    int l = 0, r = -1;
    
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    
    vector<int> d2(n, 0);  // even radii
    l = 0; r = -1;
    
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    
    return {d1, d2};
}

// 计算从每个位置开始的最长回文串
map<string, vector<int>> longest_palindromes_per_start(const string& s) {
    int n = s.length();
    auto [d1, d2] = manacher(s);
    
    // buckets: 对于每个左边界L，记录哪些中心i的左边界等于L
    vector<vector<int>> buckets_odd(n);
    vector<vector<int>> buckets_even(n);
    
    for (int i = 0; i < n; i++) {
        int left_odd = i - (d1[i] - 1);
        buckets_odd[left_odd].push_back(i);
        
        int left_even = i - d2[i];
        if (d2[i] > 0) {
            buckets_even[left_even].push_back(i);
        }
    }
    
    // 扫描L从0到n-1，维护遇到的最大中心索引i
    vector<int> ans_len(n, 1);  // 至少是单字符
    int cur_max_i_odd = -1e9;
    int cur_max_i_even = -1e9;
    
    for (int L = 0; L < n; L++) {
        // 添加左边界为L的中心
        if (!buckets_odd[L].empty()) {
            cur_max_i_odd = max(cur_max_i_odd, *max_element(buckets_odd[L].begin(), buckets_odd[L].end()));
        }
        if (!buckets_even[L].empty()) {
            cur_max_i_even = max(cur_max_i_even, *max_element(buckets_even[L].begin(), buckets_even[L].end()));
        }
        
        // 奇数候选：需要 cur_max_i_odd >= L
        if (cur_max_i_odd >= L) {
            int cand = 2 * (cur_max_i_odd - L) + 1;
            if (cand > ans_len[L]) {
                ans_len[L] = cand;
            }
        }
        
        // 偶数候选：需要 cur_max_i_even > L
        if (cur_max_i_even > L) {
            int cand = 2 * (cur_max_i_even - L);
            if (cand > ans_len[L]) {
                ans_len[L] = cand;
            }
        }
    }
    
    // 构建返回结果
    vector<int> longest_centered_odd(n);
    vector<int> longest_centered_even(n);
    
    for (int i = 0; i < n; i++) {
        longest_centered_odd[i] = 2 * d1[i] - 1;
        longest_centered_even[i] = 2 * d2[i];
    }
    
    map<string, vector<int>> result;
    result["d1"] = d1;
    result["d2"] = d2;
    result["longest_centered_odd_lengths"] = longest_centered_odd;
    result["longest_centered_even_lengths"] = longest_centered_even;
    result["longest_start_len"] = ans_len;
    
    return result;
}

int main() {
    string s = "abaac";
    auto res = longest_palindromes_per_start(s);
    
    cout << "d1 (odd radii): ";
    for (int x : res["d1"]) cout << x << " ";
    cout << "\n";
    
    cout << "odd centered lengths: ";
    for (int x : res["longest_centered_odd_lengths"]) cout << x << " ";
    cout << "\n";
    
    cout << "d2 (even radii): ";
    for (int x : res["d2"]) cout << x << " ";
    cout << "\n";
    
    cout << "even centered lengths: ";
    for (int x : res["longest_centered_even_lengths"]) cout << x << " ";
    cout << "\n";
    
    cout << "longest palindrome length starting at each index: ";
    for (int x : res["longest_start_len"]) cout << x << " ";
    cout << "\n";
    
    // 打印具体子串示例
    cout << "\nPalindrome substrings starting at each index:\n";
    for (int i = 0; i < s.length(); i++) {
        cout << "Index " << i << ": " << s.substr(i, res["longest_start_len"][i]) << "\n";
    }
    
    return 0;
}