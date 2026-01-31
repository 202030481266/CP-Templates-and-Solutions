constexpr int ALPHABET_SIZE = 26;
constexpr int MAX_STATES = 200'000;

int transitions[MAX_STATES][ALPHABET_SIZE];
int sufflink[MAX_STATES];
int escape[MAX_STATES];
int states = 1;

class AhoCorasick {
public:
	// 使用addString插入各种字符串
	int addString(const string &s) {
	    int v = 0;
	    for (char c : s) {
	        c -= 'a';
	        if (transitions[v][c] == 0) {
	            transitions[v][c] = states++;
	        }
	        v = transitions[v][c];
	    }
	    escape[v] = v;
	    return v;
	}
	// 建立联系
	void buildLinks() {
	    vector<int> q(MAX_STATES);
	    for (int s = 0, t = 1; s < t;) {
	        int v = q[s++];
	        int u = sufflink[v];
	        if (escape[v] == 0) {
	            escape[v] = escape[u];
	        }
	        for (int c = 0; c < ALPHABET_SIZE; c++) {
	            if (transitions[v][c] != 0) {
	                q[t++] = transitions[v][c];
	                sufflink[transitions[v][c]] = v != 0 ? transitions[u][c] : 0;
	            } else {
	                transitions[v][c] = transitions[u][c];
	            }
	        }
	    }
	}
};