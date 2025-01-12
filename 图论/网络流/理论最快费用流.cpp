#define UP(i,s,e) for(auto i=s; i!=e; ++i)
#define IT(i,x) for(int i=head[x]; i!=EDGE_NIL; i=es[i].nxt)
typedef long long ll;
constexpr int V = 5e3+100, E = V+5e4+100;
constexpr int EDGE_NIL = 0;
struct Edge{
	int to;
	ll lf, cost;
	int nxt;
} es[E*2+4];
ll sumcost = 0, sumflow = 0;
int is, it, iv;
ll minc, maxf;
int head[V], cnt = (EDGE_NIL|1)+1;
ll pi[V]; // h 函数
int fe[V], mark[V], timecur = 2; // fe: father edge
int fa[V];
void init(int s, int t,int v){
	is = s, it = t, iv = v+2;
	fill(head, head+iv, EDGE_NIL);
	fill(mark, mark+iv, 0);
	fill(fe, fe+iv, EDGE_NIL);
	timecur = 2;
	cnt = (EDGE_NIL|1)+1;
	sumcost = sumflow = 0;
	minc = maxf = 0;
}
void addflow(int s, int t, ll f, ll c=0){
	es[cnt] = (Edge){t, f, c, head[s]}, head[s] = cnt++;
	es[cnt] = (Edge){s, 0, -c, head[t]}, head[t] = cnt++;
	sumflow += f, sumcost += abs(c);
}
void mktree(int x, int from_e){
	fe[x] = from_e;
	fa[x] = es[from_e^1].to;
	mark[x] = 1;
	for(int i=head[x]; i!=EDGE_NIL; i=es[i].nxt){
		if(mark[es[i].to] == 1 || es[i].lf == 0) continue;
		mktree(es[i].to, i);
	}
}
ll getpi(int x){ // 获取某个点的 h 值
	if(mark[x] == timecur) return pi[x];
	mark[x] = timecur;
	pi[x] = getpi(fa[x]) - es[fe[x]].cost;
	return pi[x];
}
ll pushflow(int e){ // 返回减少的费用
	int rt = es[e].to, lca = es[e^1].to;
	timecur++;
	while(rt){ // rt 用来标记点
		mark[rt] = timecur;
		rt = fa[rt];
	}
	while(mark[lca] != timecur){ // lca 用来找 LCA
		mark[lca] = timecur;
		lca = fa[lca];
	}
	ll df = es[e].lf; // df 为流量的改变量
	int todel = e, dir = -1; // dir: direction, dir 为 0 表示 es[e].to 方向
	for(int i=es[e^1].to; i!=lca; i=fa[i]){ // 两边向上找能推的最小流
		if(es[fe[i]].lf < df){
			df = es[fe[i]].lf;
			todel = fe[i];
			dir = 1;
		}
	}
	for(int i=es[e].to; i!=lca; i=fa[i]){
		if(es[fe[i]^1].lf < df){
			df = es[fe[i]^1].lf;
			todel = fe[i];
			dir = 0;
		}
	}
	ll dcst = 0; // delta cost
	if(df) { // 推流
		for(int i=es[e].to; i!=lca; i=fa[i]){
			es[fe[i]].lf += df;
			es[fe[i]^1].lf -= df;
			dcst += es[fe[i]^1].cost * df;
		}
		for(int i=es[e^1].to; i!=lca; i=fa[i]){
			es[fe[i]].lf -= df;
			es[fe[i]^1].lf += df;
			dcst += es[fe[i]].cost * df;
		}
		es[e].lf -= df;
		es[e^1].lf += df;
		dcst += es[e].cost * df;
	}
	if(todel == e) return dcst;
	int last = e^dir, lastu = es[e^dir^1].to;
	for(int i=es[e^dir].to; i!=es[todel^1].to; ){
		mark[i]=timecur-1;
		int i_ = fa[i];
		fa[i] = lastu;
		lastu = i;
		swap(fe[i], last);
		last ^= 1;
		i=i_;
	}
	return dcst;
}
void find(){
	vector<int>dep(iv,1e9);
	dep[is]=0;
	queue<int>q;q.push(is);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=es[i].nxt){
			int v=es[i].to;
			if(es[i].lf>0&&dep[v]==1e9){
				q.push(v);
				dep[v]=dep[u]+1;
			}
		}
	}
}
void mcmf(){
	ll sfl_ = sumflow, scs_ = sumcost;
	addflow(iv-1, is, sfl_, 0);
	addflow(it, iv-1, sfl_, -scs_-1);
	sumflow = sfl_, sumcost = scs_;
	mktree(iv-1, EDGE_NIL);
	mark[iv-1] = ++timecur;
	fa[iv-1] = 0;
	bool run = true;
	while(run){
		run = false;
		UP(i, (EDGE_NIL|1)+1, cnt){
			int s = es[i^1].to, t = es[i].to;
			if(es[i].lf && es[i].cost + getpi(t) - getpi(s) < 0){
				run = true;
				minc += pushflow(i);
			}
		} // 一圈下来没流可推时算法结束
	}
	maxf = es[cnt-1].lf;
	minc += maxf * (scs_+1);
}
//可以解决负环问题
