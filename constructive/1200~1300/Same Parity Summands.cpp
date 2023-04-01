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




void solve() {
    int n, k;
    cin >> n >> k;
    if (n < k) {
        // impossible
        cout << "NO" << endl;
        return;
    }
    if ((n - k) % 2 == 0) {
        // can be divided into odd numbers
        cout << "YES" << endl;
        for (int i = 0; i < k - 1; ++i) cout << 1 << ' ';
        cout << (n - k + 1) << endl;
        return;
    }
    if (n >= 2 * k && (n - 2 * k) % 2 == 0) {
        // can be divided into even numbers
        cout << "YES" << endl;
        for (int i = 0; i < k - 1; ++i) cout << 2 << ' ';
        cout << (n - 2 * k + 2)  << endl;
        return;
    }
    cout << "NO" << endl;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}













