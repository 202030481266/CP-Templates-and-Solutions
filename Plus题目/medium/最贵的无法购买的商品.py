from math import gcd
def extended_euclid(a, b):
    if b == 0:
        return a, 1, 0
    else:
        gcd, x1, y1 = extended_euclid(b, a % b)
        x = y1
        y = x1 - y1 * (a // b)
        return gcd, x, y
def inverse(a, m):
    gcd, x, y = extended_euclid(a, m)
    if gcd != 1:
        return -1  # modular inverse doesn't exist
    else:
        return (x % m + m) % m
class Solution:
    def mostExpensiveItem(self, primeOne: int, primeTwo: int) -> int:
        # 数学, x*p1+y*p2 无法表示的最大整数,由于p1,p2互质，所以x*p1+y*p2永远有解
        # 但是x,y不能为负数，这就使得存在最大的无法购买的商品
        g,x,y = extended_euclid(primeOne,primeTwo)
        # x=x0*c+primeTwo*t
        # y=y0*c-primeOne*t
        x=abs(x)
        y=abs(y)
        k=min(x*primeOne,y*primeTwo)
        left=0
        v=x*y//gcd(x,y)
        ans = 0
        for i in range(1,k+1):
            # (left,i)
            p = (i*k-1) - (i*k-1)%v
            if p > left:
                ans = p//v
            left=i*(k+1)
        return ans
# 本题实际上存在一个定理：麦乐鸡定理,即对于互质的两个数a,b,存在一个数N,使得N无法表示为a*x+b*y的形式，那么个数字最大为a*b-a-b
                
            

            
    
        
