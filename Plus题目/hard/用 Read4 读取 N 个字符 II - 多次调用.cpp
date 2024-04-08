// 这道题目是困难我笑了
class Solution {
public:
    char *buf4 = new char[4];
    int buf4Index = 0;
    int buf4Size = 0;
    int read(char *buf, int n) {
        int index = 0;
        while(index<n){
            while(buf4Index<buf4Size && index<n){
                buf[index++] = buf4[buf4Index++];
            }
            if(index<n){
                buf4Size = read4(buf4);
                buf4Index = 0;
                if(buf4Size==0) break;
            }
        }
        return index;
    }
};

