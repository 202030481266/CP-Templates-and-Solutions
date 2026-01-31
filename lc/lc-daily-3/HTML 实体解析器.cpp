class Solution {
public:
    string replaceAll(string str, const string& from, const string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
        return str;
    }
    string multiReplace(string str, const unordered_map<string, string>& replacements) {
        vector<pair<size_t, string>> positions; // 存储替换位置和对应的原字符串

        // 查找所有替换位置
        for (const auto& pair : replacements) {
            const string& from = pair.first;
            size_t start_pos = 0;
            while ((start_pos = str.find(from, start_pos)) != string::npos) {
                positions.emplace_back(start_pos, from);
                start_pos += from.length();
            }
        }

        // 按位置逆序排序，以便从后往前替换
        sort(positions.begin(), positions.end(), [](const pair<size_t, string>& a, const pair<size_t, string>& b) {
            return a.first > b.first;
        });

        // 执行替换
        for (const auto& pos : positions) {
            const string& original = pos.second;
            str.replace(pos.first, original.length(), replacements.at(original));
        }

        return str;
    }
    string entityParser(string text) {
        vector<string> source{"&quot;", "&apos;", "&amp;", "&gt;", "&lt;", "&frasl;"};
        vector<string> target{"\"", "'", "&", ">", "<", "/"};
        unordered_map<string, string> mp
        for (int i = 0; i < source.size(); ++i) 
            mp[source[i]] = target[i];
        return multiReplace(text, mp);
    }
};