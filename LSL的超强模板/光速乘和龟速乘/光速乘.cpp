
typedef long long ll;
// 计算 a*b mod p


ull mul(ull a, ull b, ull p) { // ull 是 unsigned long long 类型，ll 是long long类型
    a %= p, b %= p;
    ull c = (long double)a * b / p;
    ull x = a * b, y = c * p;
    ll ans = (long long)(x % p) - (long long)(y % p);
    if(ans < 0) ans += p;
    return ans;
}


// 范围不大的情况下下面的函数更加快速
inline ll q_mul(ll x, ll y, ll P){
    ll L=x*(y>>25)%P*(1<<25)%P;
    ll R=x*(y&((1<<25)-1))%P;
    return (L+R)%P;
}