#include <bits/stdc++.h>
using namespace std;

namespace KMP {
    std::vector<int> build_lps(std::string p) {
        std::vector<int> lps(p.size() + 1);
        int j = 0;
        lps[0] = 0;
        for (int i = 1; i < p.size(); ++i) {
            while (j >= 0 && p[i] != p[j]) {
                if (j > 0) j = lps[j - 1];
                else j = -1;
            }
            ++j;
            lps[i] = j;
        }
        return lps;
    }
    int find_first_of_p(std::vector<int>& lps, std::string s, std::string p) {
        int p_sz = p.size(), s_sz = s.size();
        int j = 0;
        for (int i = 0; i < s_sz; ++i) {
            while (j >= 0 && s[i] != p[j]) {
                if (j > 0) j = lps[j - 1];
                else j = -1;
            }
            ++j;
            if (j == p_sz) {
                return i - p_sz + 1; // [i - p_sz + 1, i]
            }
        }
        return -1;
    }
    std::vector<int> find_all_of_p(std::vector<int>& lps, std::string s, std::string p) {
        std::vector<int> result;
        int p_sz = p.size(), s_sz = s.size();
        int j = 0;
        for (int i = 0; i < s_sz; ++i) {
            while (j >= 0 && s[i] != p[j]) {
                if (j > 0) j = lps[j - 1];
                else j = -1;
            }
            ++j;
            if (j == p_sz) {
                result.push_back(i - p_sz + 1);
                j = lps[j - 1];
            }
        }
        return result;
    }
    // exKMP 扩展KMP算法
    // 解决文本串s的所有后缀和模式串p的最长公共前缀的问题
    // 通常来说求解模式串p自身的最长公共前缀算法叫做Z Algorithm
    std::vector<int> z_function(std::string p) {
        std::vector<int> z(p.size());
        for (int i = 1, l = 0, r = 0; i < p.size(); ++i) {
            if (i <= r) z[i] = std::min(z[i - l], r - i + 1);
            while (i + z[i] < p.size() && p[i + z[i]] == p[z[i]]) ++z[i];
            if (i + z[i] - 1 > r) {
                r = i + z[i] - 1;
                l = i;
            }
        }
        z[0] = p.size();// 最后需要赋值一下
        return z;
    }
    std::vector<int> build_z_of_s(std::vector<int>& z, std::string s, std::string p) {
        std::vector<int> lcp(s.size());
        while (lcp[0] < s.size() && lcp[0] < p.size() && s[lcp[0]] == p[lcp[0]]) ++lcp[0];
        for (int i = 1, l = 0, r = lcp[0] - 1; i < s.size(); ++i) {
            if (i <= r) lcp[i] = std::min(z[i - l], r - i + 1);
            while (i + lcp[i] < s.size() && lcp[i] < p.size() && s[i + lcp[i]] == p[lcp[i]]) ++lcp[i];
            if (i + lcp[i] - 1 > r) {
                r = i + lcp[i] - 1;
                l = i;
            }
        }
        return lcp;
    }
}


// https://www.luogu.com.cn/problem/P5410

int main() {
    std::string s, p;
    cin >> s >> p;
    std::vector<int> pz = KMP::z_function(p);
    std::vector<int> sz = KMP::build_z_of_s(pz, s, p);
    long long ans = 0;
    for (int i = 0; i < pz.size(); ++i)
        ans ^= 1ll * (i + 1) * (pz[i] + 1);
    cout << ans << endl;
    ans = 0;
    for (int i = 0; i < sz.size(); ++i)
        ans ^= 1ll * (i + 1) * (sz[i] + 1);
    cout << ans << endl;
}