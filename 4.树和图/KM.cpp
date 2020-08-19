//1. init() 初始化边权
//2. add(u, v, w) 连一条u到v的边
//3. KM() 二分图最大权完备匹配
// O(n^3)
namespace KM {
    ll cost[MAXN][MAXN], ans, slack[MAXN], ex[MAXN], ey[MAXN];//double换类型
    ll mat[MAXN], pre[MAXN], visy[MAXN], n;
    void init() {
        memset(cost, -0x7f, sizeof cost);
    }
    void clear() {
        memset(mat, -1, sizeof mat);
        memset(ex, 0, sizeof ex);
        memset(ey, 0, sizeof ey);
        ans = 0;
    }
    void add(ll u, ll v, ll w) {
        cost[u][v] = w; 
    }
    void match(ll u) {
        ll x, y = 0, yy = 0;
        ll delta; //double换类型
        memset(pre, 0, sizeof pre);
        for(int i = 1; i <= n; i++) slack[i] = Linf;
        mat[y] = u;
        while(true) {
            x = mat[y]; delta = Linf; visy[y] = 1;
            for(ll i = 1; i <= n; i++) {
                if(visy[i]) continue;
                if(slack[i] > ex[x] + ey[i] - cost[x][i]) {
                    slack[i] = ex[x] + ey[i] - cost[x][i];
                    pre[i] = y;
                }
                if(slack[i] < delta) delta = slack[i], yy = i;
            }
            for(int i = 0; i <= n; i++) {
                if(visy[i]) ex[mat[i]] -= delta, ey[i] += delta;
                else slack[i] -= delta;
            }
            y = yy;
            if(mat[y] == -1) break;
        }
        while(y) mat[y] = mat[pre[y]], y = pre[y];
    }
    ll KM() {
        clear();
        for(ll i = 1; i <= n; i++) {
            memset(visy, 0, sizeof visy);
            match(i);
        }
        ans = 0;
        for(ll i = 1; i <= n; i++) 
            if(mat[i] != -1) ans += cost[mat[i]][i];
        return ans;
    }
}
