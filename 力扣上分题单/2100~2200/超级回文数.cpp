// https://leetcode.cn/problems/super-palindromes/



// 打表法，因为数字绝对是非常少的，因为不能保证有进位
class Solution {
public:
    int superpalindromesInRange(string left, string right) {
    	vector<long long> res{1,2,3,11,22,101,111,121,202,212,1001,1111,2002,10001,10101,10201,
    			              11011,11111,11211,20002,20102,100001,101101,110011,111111,200002,
    			              1000001,1001001,1002001,1010101,1011101,1012101,1100011,1101011,1102011,
    			              1110111,1111111,2000002,2001002,10000001,10011001,10100101,10111101,11000011,
    			              11011011,11100111,11111111,20000002,100000001,100010001,100020001,100101001,
    			              100111001,100121001,101000101,101010101,101020101,101101101,101111101,110000011,
    			              110010011,110020011,110101011,110111011,111000111,111010111,111101111,111111111,200000002,200010002};
    	long long l = stoll(left), r = stoll(right), cnt = 0;
    	for (int i = 0 ; i < res.size(); ++i) 
    		if (res[i] * res[i] <= r && res[i] * res[i] >= l) ++cnt;
    	return cnt;
    }
};


// 正解（反正也是暴力枚举）
class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        int res = 0;
        long l = stol(left);
        long r = stol(right);

        // 先判断偶数的情况 ABCCBA
        for (int i = 1; i < 100000; ++i)
        {
            string s = to_string(i);
            string s2 = s;
            reverse(s2.begin(), s2.end());
            long m= stol(s + s2);
            m *= m;
            // 超过范围提前结束遍历
            if (m > r)
            {
                break;
            }
            else if (m >= l && IsPalindrom(m))
            {
                ++res;
            }
        }

        // 再判断奇数的情况 ABCBA
        for (int i = 1; i < 100000; ++i)
        {
            string s = to_string(i);
            string s2 = s;
            reverse(s2.begin(), s2.end());
            long m= stol(s.append(s2.begin()+1, s2.end()));
            m *= m;
            // 超过范围提前结束遍历
            if (m > r)
            {
                break;
            }
            else if (m >= l && IsPalindrom(m))
            {
                ++res;
            }
        }

        return res;
    }

    bool IsPalindrom(long num)
    {
        long n = num;
        // 倒序的数字
        long revNum = 0;
        while (n > 0)
        {
            revNum = revNum * 10 + n % 10;
            n /= 10;
        }
        // 直接比较是否相等即可
        return revNum == num;
    }
};

