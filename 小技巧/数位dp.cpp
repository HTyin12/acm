long long dp[100][10][100][5];
int dig[100];
int cnt;
long long dfs(int pos,int limit,int sum,int color,int f){
	if(pos==0){
		return sum;
	}
	if(dp[pos][color][sum][f]!=-1&&(!limit))return dp[pos][color][sum][f];
	long long res=0;
	int up=limit?dig[pos]:9;
	for(int i=0;i<=up;i++){
		res+=dfs(pos-1,limit&&i==up,sum+(i==color&&(f||i)),color,i||f);
	}
	if(limit)return res;
	return dp[pos][color][sum][f]=res;
}
long long ask(long long x,int color){
	cnt=0;
	while(x){
		dig[++cnt]=x%10;x/=10;
	}
	return dfs(cnt,1,0,color,0);
}
