// logn时间复杂度判断一个数n是否是素数
namespace Miller_Rabin{ // 大素数检测，
    ll mul(ll a, ll b, ll p){
        return (a * b - (ll)((long double)a / p * b) * p + p) % p;
    }
    ll pow(ll a,ll b,ll p){
        ll ans = 1;
        while(b){
            if(b & 1)ans = mul(ans, a, p);//a和b可能很大
            b >>= 1;
            a = mul(a,a,p);
        }
        return ans;
    }
    bool miller_rabin(ll n){
        if(n == 2)return 1;
        if(n < 2 || !(n & 1))return 0;
        ll u,t;
        for(t = 0,u = n - 1; !(u & 1); t++,u>>=1);//n-1 =u*2^t
        for(int i = 0; i < 10; i++){//10次试探
            ll a = rand() % (n - 1) + 1;//a∈[1,n)
            ll x = pow(a, u, n);
            for(int j = 0; j < t; j++){//二次试探
                ll y = mul(x, x, n);
                if(y == 1 && x != 1 && x != n - 1)
                    return 0;
                x = y;//相当于让幂重新变回p - 1
            }
            if(x != 1)return 0;
        }
        return 1;
    }
    bool isPrime(ll n){ // 判断大整数是否是素数
        return miller_rabin(n);
    }
};

// log时间复杂度获得一个数的因子，获取最大质因子模板
namespace Pollard_Rho{
    ll maxp;
    inline ll llabs(ll x){
        return x > 0 ? x : -x;
    }
    inline ll mul(ll a, ll b, ll mod) { // O(1)快速乘
        return (a * b - (ll)((long double)a * b / mod) * mod + mod) % mod;
    }
    inline ll pow(ll a, ll b, ll mod) { // O(logn)快速幂
        ll ans = 1 % mod; a = a % mod;
        while (b) {
            if (b & 1) ans = mul(ans, a, mod);
            a = mul(a, a, mod), b >>= 1;
        }
        return ans;
    }  
    bool miller_rabin(ll n){ // 大素数检测
        if(n == 2)return 1;
        if(n < 2 || !(n & 1))return 0;
        ll u,t;
        for(t = 0,u = n - 1; !(u & 1); t++,u>>=1);//n-1 =u*2^t
        for(int i = 0; i < 10; i++){//10次试探
            ll a = rand() % (n - 1) + 1;//a∈[1,n)
            ll x = pow(a,u,n);
            for(int j = 0; j < t; j++){//二次试探
                ll y = mul(x,x,n);
                if(y == 1 && x != 1 && x != n - 1)
                    return 0;
                x = y;//相当于让幂重新变回p - 1
            }
            if(x != 1)return 0;
        }
        return 1;
    }
    inline ll f(ll x, ll c, ll mod) { 
        return (mul(x, x, mod) + c) % mod;
    }
    inline ll gcd(ll a, ll b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    inline ll pollard_rho(ll x) {
        ll c = rand() % x, s = 0, t = 0, val = 1;
        for (int goal = 1; ; goal *= 2, s = t, val = 1) {
            for (int step = 1; step <= goal; ++step) {
                t = f(t, c, x);
                val = mul(val, llabs(s - t), x);
                if (step % 127 == 0) {
                    ll d = gcd(val, x);
                    if (d > 1) return d;
                }
            }
            ll d = gcd(val, x);
            if (d > 1) return d;
        }
    } 
    void solve(ll x) { // 获取n的所有因子
        if (x < maxp || x < 2) return;
        if (miller_rabin(x)) {
            if (x > maxp) maxp = x;
            return;
        }
        ll p = x;
        while (p == x) p = pollard_rho(x);
        while (x % p == 0) x /= p;
        solve(x), solve(p);
    }
    ll maxfac(ll n){ // 获得最大的质因子
        maxp = 0;
        solve(n);
        return maxp;
    }
};
