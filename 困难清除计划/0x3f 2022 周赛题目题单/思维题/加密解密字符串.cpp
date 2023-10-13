// 逆向思维
class Encrypter {
    array<string, 26> mp;
    unordered_map<string, int> cnt;
public:
    Encrypter(vector<char> &keys, vector<string> &values, vector<string> &dictionary) {
        for (int i = 0; i < keys.size(); ++i)
            mp[keys[i] - 'a'] = values[i];
        for (auto &s : dictionary)
            ++cnt[encrypt(s)];
    }

    string encrypt(string word1) {
        string res;
        for (char ch : word1) {
            auto &s = mp[ch - 'a'];
            if (s == "") return "";
            res += s;
        }
        return res;
    }

    int decrypt(string word2) { return cnt.count(word2) ? cnt[word2] : 0; } // 防止把不在 cnt 中的字符串加进去
};

