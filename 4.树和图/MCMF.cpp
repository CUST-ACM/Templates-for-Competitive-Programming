// add_edge(u, v, w, c) 连一条u到v的单向边，容量为w，花费为c，并且增加反向边
// doit(S, T, &flow, &cost), 以S为源点，T为汇点的最小费用最大流，flow为最大流量，cost为最小费用
// init() 清空边
namespace MCMF {  
    int cnt, head[MAXN];  
    int dis[MAXN], vis[MAXN], pre[MAXN];  
    struct Edge {  
        int u, to, w, c, next;  
    }edge[MAXN<<1];     
    void init() {  
        cnt = 0;  
        memset(head, -1, sizeof head);  
    }  
    void add(int u, int v, int w, int c) {  
        edge[cnt].u = u;  
        edge[cnt].to = v;  
        edge[cnt].w = w;  
        edge[cnt].c = c;  
        edge[cnt].next = head[u];  
        head[u] = cnt++;  
    }  
    void add_edge(int u, int v, int w, int c) {  
        add(u, v, w, c); add(v, u, 0, -c);  
    }  
    bool spfa(int S, int T) {  
        memset(dis, 0x3f, sizeof dis);  
        memset(vis, 0, sizeof vis);  
        memset(pre, -1, sizeof pre);  
        queue<int> q;  
        q.push(S); vis[S] = 1; dis[S] = 0;  
        while(!q.empty()) {  
            int u = q.front(); q.pop(); vis[u] = 0;  
            for(int i = head[u]; i != -1; i = edge[i].next) {  
                int v = edge[i].to;  
                if(edge[i].w > 0 && dis[v] > dis[u] + edge[i].c) {  
                    dis[v] = dis[u] + edge[i].c;  
                    pre[v] = i;  
                    if(!vis[v]) vis[v] = 1, q.push(v);  
                }  
            }  
        }  
        return pre[T] != -1;  
    }  
    void doit(int S, int T, int &flow, int &cost) {
        flow = 0; cost = 0;  
        while(spfa(S, T)) {  
            int x = Inf;  
            for(int i = T; i != S; i = edge[pre[i]^1].to) x = min(x, edge[pre[i]].w);  
            flow += x;  
            for(int i = T; i != S; i = edge[pre[i]^1].to) {  
                int k = pre[i];  
                edge[k].w -= x;  
                edge[k^1].w += x;  
                cost += x * edge[k] .c;  
            }  

        }  
    }  
}
