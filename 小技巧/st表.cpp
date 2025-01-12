int lg[N];
struct ST // 内存26w 开2个int
{
	ll mi, mx;
} st[N][21];
void pu (ST &u, ST &l, ST &r)
{
	u.mi = min (l.mi, r.mi);
	u.mx = max (l.mx, r.mx);
}
void work()
{
	for(int i=2;i<=n;i++) lg[i] = lg[i / 2] + 1;
	for(int i=1;i<=n;i++)
	{
		long long x = a[i];
		st[i][0] = {x, x};
	}
	for(int i=1;i<=20;i++)for(int j=1;j<=n + 1 - (1 << i);j++)
	{
		pu (st[j][i], st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
	}
}
ST Q (int l, int r)
{
	int t = lg[r - l + 1];
	ST s = {0};
	pu (s, st[l][t], st[r + 1 - (1 << t)][t]);
	return s;
};
work();
