// https://leetcode.cn/problems/prime-palindrome/
// 很麻烦的一道题目，总之就是要构造，并且有相对应的技巧


class Solution {
public:
    int primePalindrome(int N) {
        for(int i=N;i<=11;i++)//小于10直接判断；11 要单独判断，因为偶数长度的回文数，奇数位上数字之和=偶数位上数字之和，是11的倍数，所以不是素数
            if(isPrime(i))
                return i;
        bool found=false;
        int m=N, l=0;
        while(m){//找到N的长度
            m/=10;
            l++;
        }
        for(int i=l/2;i<5;i++){//从N的长度的一半开始构建回文数，长度最多是9，因为题目说答案小于 2 * 10^8
            string str(i*2+1,'0');//奇数长度，l*2+1 ~ 9
            makePalindrome(N, str, i*2, 0, i*2, found);
            if(found)
                return strToInt(str);
        }
        return -1;
    }

    void makePalindrome(const int &N, string &str, const int len, int l, int r, bool &found){//从左右两端向里面构建长度为 len+1 的回文数
        if(found)
            return;
        if(l>r){//构建完回文数，判断是不是素数
            int m=strToInt(str);
            found = (m>=N) && isPrime(m);
            return;
        }
        bool begin = (r==len);//判断是不是回文数最外面一位
        for(int i=0;i<10;i++){//每一位从0到9遍历
            if(found)
                return;
            if( begin && (i%2==0||i==5) )//个位是2的倍数或者5肯定不是素数
                continue;
            str[l]=str[r]='0'+i;
            makePalindrome(N,str,len,l+1,r-1,found);//从外到内，从小到大构建回文数
        }
    }

    bool isPrime(int x){
        if(x<=1)
            return false;
        for(int i=2;i*i<=x;i++)
            if(x%i==0)
                return false;
        return true;
    }

    int strToInt(const string &s){
        int x=0;
        for(int i=0;i<s.size();i++)
            x=(x<<3)+(x<<1)+(s[i]-'0');// x*8 + x*2 = x*10
        return x;
    }
};

