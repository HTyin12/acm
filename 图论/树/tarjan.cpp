const int N=2e5+5;
int cnt;
int low[N],num[N],dfn,sccno[N],Stack[N],top,cut[N],root;
vector<int>G[N];
void dfs(int u,int fa){
	Stack[top++]=u;
	low[u]=num[u]=++dfn;
	int child=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		// if(v==fa)continue;
		if(!num[v]){
			child++;
			dfs(v,u);
			low[u]=min(low[v],low[u]);
			if(low[v]>=num[u]&&u!=root)cut[u]=1;
		}
		else if(!sccno[v]){
			low[u]=min(low[u],num[v]);
		}
		
	}
	if(u==root&&child>=2)cut[u]=1;
	if(low[u]==num[u]){
		cnt++;
		while(1){
			int v=Stack[--top];
			sccno[v]=cnt;
			if(u==v)break;
		}
	}
}
void tarjan(int n){
	cnt=top=dfn=0;
	for(int i=1;i<=n;i++)num[i]=sccno[i]=cut[i]=0;
	for(int i=1;i<=n;i++)if(!num[i])
		root=i,dfs(i,0);
}
