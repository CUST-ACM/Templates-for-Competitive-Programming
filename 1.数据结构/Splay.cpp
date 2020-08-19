// 1. Build(0, n+1, 0) 把a序列[1,n]的数变成一棵Splay，0和n+1,为人为添加的点
// 2. kth(k),查询Splay中第k个数
// 3. Reverse(x, y),反转区间[x,y]
// 4. Insert(pos, x), 把数值为x的数插入到位置pos后面
// 5. Delete(pos), 把pos位置的数删除
// 6. Add(x, y, C), 把区间[x,y]都加上C
// 7. GetMin(x, y), 寻找区间[x,y]中最小的数
// 8. OutPut(root, vec), vec为答案数组，[1,n],0和n+1为添加数

namespace Splay {
	int fa[MAXN], ch[MAXN][2], val[MAXN], addv[MAXN], siz[MAXN], rev[MAXN], mn[MAXN];
	int st[MAXN], root, tot;
	void Rev(int x) {
		if(!x) return;
		swap(ch[x][0], ch[x][1]);
		rev[x] ^= 1;
	}
	void Add(int x, int C) {
		if(!x) return;
		val[x] += C; mn[x] += C; addv[x] += C;
	}
	void PushDown(int x) {
		if(rev[x]) {
			if(ch[x][0]) Rev(ch[x][0]);
			if(ch[x][1]) Rev(ch[x][1]);
			rev[x] ^= 1;
		}
		if(addv[x]) {
			if(ch[x][0]) Add(ch[x][0], addv[x]);
			if(ch[x][1]) Add(ch[x][1], addv[x]);
			addv[x] = 0;
		}
	}
	void PushUp(int x) {
		siz[x] = 1; mn[x] = val[x]; 
		if(ch[x][0]) siz[x] += siz[ch[x][0]], mn[x] = min(mn[x], mn[ch[x][0]]);
		if(ch[x][1]) siz[x] += siz[ch[x][1]], mn[x] = min(mn[x], mn[ch[x][1]]);
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y], k = ch[y][1] == x, w = ch[x][!k];
		if(fa[y]) ch[z][ch[z][1]==y] = x; 
		ch[x][!k] = y; ch[y][k] = w;
		if(w) fa[w] = y;
		fa[x] = z; fa[y] = x; 
		PushUp(y); PushUp(x);
	}
	void Splay(int x, int goal) {
		int y = x, top = 0; st[++top] = y;
		while(fa[y]) st[++top] = fa[y], y = fa[y];
		while(top) PushDown(st[top--]);
		while(fa[x] != goal) {
			int y = fa[x], z = fa[y];
			if(fa[y] != goal) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
			rotate(x);
		}
		if(!goal) root = x;
		PushUp(x);
	}
	int kth(int k) {
		int x = root, cur;
		while(true) {
			PushDown(x);
			cur = siz[ch[x][0]] + 1;
			if(cur == k) return x;
			if(k < cur) x = ch[x][0];
			else k -= cur, x = ch[x][1];
		}
	}
	int Build(int l, int r, int pre, int *a) {
		int x = ++tot, mid = (l + r) >> 1;
		fa[x] = pre; val[x] = a[mid];
		if(l < mid) ch[x][0] = Build(l, mid-1, x, a);
		if(r > mid) ch[x][1] = Build(mid+1, r, x, a);
		PushUp(x);
		return x;
	}
	void Reverse(int x, int y) {
		x = kth(x); y = kth(y+2);
		Splay(x, 0); Splay(y, x); Rev(ch[y][0]);
	}
	void Insert(int pos, int x) {
		int pos1 = kth(pos+1), pos2 = kth(pos+2);
		Splay(pos1, 0); Splay(pos2, pos1);
		val[++tot] = x; fa[tot] = pos2; ch[pos2][0] = tot;
		PushUp(tot); PushUp(pos2); PushUp(pos1);
	}
	void Delete(int pos) {
		int x = kth(pos), y = kth(pos+2);
		Splay(x, 0); Splay(y, x);
		ch[y][0] = 0; PushUp(y); PushUp(x);
	}
	void Add(int x, int y, int C) {
		x = kth(x); y = kth(y+2);
		Splay(x, 0); Splay(y, x); Add(ch[y][0], C);
	}
	int GetMin(int x, int y) {
		x = kth(x); y = kth(y+2);
		Splay(x, 0); Splay(y, x);
		return mn[ch[y][0]];
	}
	void OutPut(int x, vector<int> &vec) {
		PushDown(x);
		if(ch[x][0]) OutPut(ch[x][0], vec);
		vec.push_back(val[x]);
		if(ch[x][1]) OutPut(ch[x][1], vec);
	}
	void Build(int n, int *a) {
		root = Build(0, n+1, 0, a);
	}
}
