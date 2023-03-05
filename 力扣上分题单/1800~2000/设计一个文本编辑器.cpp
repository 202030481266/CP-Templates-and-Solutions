// https://leetcode.cn/problems/design-a-text-editor/



class TextEditor {
public:
	list<char> txt;
	list<char>::iterator cur;

    TextEditor() {
    	txt.clear();
    	cur = txt.begin();
    }

    void debug() {
        for (auto it = txt.begin(); it != txt.end(); ++it)
            cout << *it;
        cout << " the cursor is " << *cur << endl;
    }
    
    void addText(string text) {
    	for (char ch : text) 
    		txt.emplace(cur, ch);
    }
    
    int deleteText(int k) {
    	int x = 0;
    	while (k--) {
    		if (cur == txt.begin())
    			break;
    		txt.erase(prev(cur));
            ++x;
    	}
    	return x;
    }
    
    string cursorLeft(int k) {
        if (txt.size() == 0) return "";
    	while (k--) {
    		if (cur == txt.begin())
    			break;
    		cur = prev(cur);
    	}
    	if (cur == txt.begin()) return "";
    	string ans;
    	auto temp = prev(cur);
    	for (int i = 0; i < 10; ++i) {
    		if (temp == txt.begin()) {
                ans += (*temp);
                break;
            }
    		ans += (*temp);
    		temp = prev(temp);
    	}
    	reverse(ans.begin(), ans.end());
    	return ans;
    }
    
    string cursorRight(int k) {
        if (txt.size() == 0) return "";
    	while (k--) {
    		if (cur == txt.end())
    			break;
    		cur = next(cur);
    	}
    	string ans;
    	auto temp = prev(cur);
    	for (int i = 0; i < 10; ++i) {
    		if (temp == txt.begin()) {
                ans += (*temp);
                break;
            }
    		ans += (*temp);
    		temp = prev(temp);
    	}
    	reverse(ans.begin(), ans.end());
    	return ans;
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */