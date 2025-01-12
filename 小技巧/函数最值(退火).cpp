const double eps=1e-8; //终止温度;
int dir[2]={1,-1};
double f(double x)
{
	return  6*pow(x,7) + 8*pow(x,6) + 7*pow(x,3) + 5*pow(x,2) - y*x;
} 

double anneal(double X,double Y)
{
	double T=Y;//初始温度;
	double delta=0.98; //降温系数(一个略小于1的小数);
	double x=(X+Y)/2;//x初始值;
	double now=f(x);//计算当前函数值;
	double ans=now;
	while(T>eps)
	{
		double nowx=x+dir[rand()%2]*T;//随机改变x的值;
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