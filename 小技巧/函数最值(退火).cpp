const double eps=1e-8; //��ֹ�¶�;
int dir[2]={1,-1};
double f(double x)
{
	return  6*pow(x,7) + 8*pow(x,6) + 7*pow(x,3) + 5*pow(x,2) - y*x;
} 

double anneal(double X,double Y)
{
	double T=Y;//��ʼ�¶�;
	double delta=0.98; //����ϵ��(һ����С��1��С��);
	double x=(X+Y)/2;//x��ʼֵ;
	double now=f(x);//���㵱ǰ����ֵ;
	double ans=now;
	while(T>eps)
	{
		double nowx=x+dir[rand()%2]*T;//����ı�x��ֵ;
		if(nowx>=X&& nowx<=Y)
		{
			now=f(nowx);
			if(ans-now>eps)
			{
				ans=now;
				x=nowx;
			}
		} 
		T*=delta;
	} 
	return ans;
}