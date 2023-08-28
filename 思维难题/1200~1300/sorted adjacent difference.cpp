#include <bits/stdc++.h>

using namespace std;


string trimAll(string s, char trim) {
    string::iterator pos = s.begin();
    while (true) {
        pos = find(pos, s.end(), trim);
        if (pos == s.end()) break;
        s.erase(pos);
    }
    return s;
}
void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}
void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}
vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

// 构造整数随机数据
// 梅森素数旋转算法
vector<int> get_random_data(size_t times, int lower, int upper) {
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> u(lower, upper);
    vector<int> res;
    for (int i = 0; i < times; i++)
        res.emplace_back(u(gen));
    return res;
}
string get_random_alpha_string(size_t length) {
    auto index = get_random_data(length, 0, 25);
    string res;
    for (int i = 0; i < length; i++) res += char(index[i] + 'a');
    return res;
}
string get_random_digit_string(size_t length) {
    auto index = get_random_data(length, 0, 9);
    string res;
    for (int i = 0; i < length; i++) res += char(index[i] + '0');
    return res;
}
string get_leetcode_vector(size_t times, int lower, int upper) {
    vector<int> tmp = get_random_data(times, lower, upper);
    cout << '[';
    for (int i = 0; i < tmp.size(); ++i) {
        if (i < tmp.size() - 1) cout << tmp[i] << ',';
        else cout << tmp[i] << ']';
    }
    cout << endl;
}
void output_vector(const vector<int>& ans) {
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << (i == ans.size() - 1 ? '\n' : ' ');
    }
}



void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> ans(n);
    for (auto &c : a) cin >> c;

    sort(a.begin(), a.end());
    int l = 0, r = n - 1;
    for (int i = 0; i < n; ++i) {
        if (i & 1) {
            ans[n - 1 - i] = a[l++];
        }
        else {
            ans[n - 1 - i] = a[r--];
        }
    }
    output_vector(ans);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}













