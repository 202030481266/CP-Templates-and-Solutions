class Solution {
public:
    bool isValidSerialization(string preorder) { 
        vector<int> a;
        stringstream ss(preorder);
        string item;
        while (getline(ss, item, ',')) {
            a.push_back(item == "#" ? 0 : 1);
        }
        // for (int& v : a) cout << v << ' ' ;cout<<endl;
        stack<int> s;
        for (int& v : a) {
            if (v == 0) {
                while (s.size() >= 2 && s.top() == 0) {
                    s.pop();
                    if (s.top())
                        s.pop();
                    else return false;
                }
                s.push(0);
            }
            else s.push(1);
        }
        return s.size() == 1 && s.top() == 0;
    }
};