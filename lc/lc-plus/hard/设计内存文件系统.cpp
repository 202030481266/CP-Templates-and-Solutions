// 模拟
struct directory {
    unordered_map<string, string> files;
    unordered_map<string, directory*> dirs;
};
class FileSystem {
public:
    directory* root;
    FileSystem() {
        root = new directory();
    }

    vector<string> split(const string& s, char delim) {
        vector<string> res;
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) res.push_back(item);
        return res;
    }
    
    vector<string> ls(string path) {
        // cout << "ls" << ' ' << path << endl;
        directory* cur = root;
        string p(path.begin() + 1, path.end());
        vector<string> names = split(p, '/');
        vector<string> result;
        for (string& n : names) {
            if (cur->dirs.count(n)) {
                cur = cur->dirs[n];
            }
            else {
                return {n}; // is a file
            }
        }
        for (auto it = cur->files.begin(); it != cur->files.end(); ++it)
            result.push_back(it->first);
        for (auto it = cur->dirs.begin(); it != cur->dirs.end(); ++it)
            result.push_back(it->first);
        sort(result.begin(), result.end());
        return result;
    }
    
    void mkdir(string path) {
        // cout << "mkdir" << ' ' << path << endl;
        directory* cur = root;
        string p(path.begin() + 1, path.end());
        vector<string> names = split(p, '/');
        for (string& n : names) {
            if (!cur->dirs.count(n)) {
                cur->dirs[n] = new directory();
            }
            cur = cur->dirs[n];
        }
    }
    
    void addContentToFile(string filePath, string content) {
        // cout <<"addcontent" << ' ' << filePath << ' ' << content << endl;
        directory* cur = root;
        string p(filePath.begin() + 1, filePath.end());
        vector<string> names = split(p, '/');
        for (string& n : names) {
            if (cur->dirs.count(n)) {
                cur = cur->dirs[n];
            }
            else {
                // is the file
                cur->files[n] += content;
            }
        }
    }
    
    string readContentFromFile(string filePath) {
        // cout <<"readcontent" << ' ' << filePath << endl;
        directory* cur = root;
        string p(filePath.begin() + 1, filePath.end());
        vector<string> names = split(p, '/');
        string res;
        for (string& n : names) {
            if (cur->dirs.count(n)) {
                cur = cur->dirs[n];
            }
            else {
                res = cur->files[n];
            }
        }
        return res;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */