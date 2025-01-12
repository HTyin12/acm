#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int prime[N];
int Prime[N];//素数为0  1要特判
int euler(int n){
	int cnt=0;
	for(int i=2;i<=n;i++){
		if(!Prime[i])prime[++cnt]=i;
		for(int j=1;prime[j]*i<=n;j++){
			Prime[prime[j]*i]=prime[j];
			if(i%prime[j]==0)break;
		}
	}
	return cnt;
}
bool isprime(int num){//O(sqrt(n)/3)
    if(num==1)return false;
    if(num==2||num==3)return true;
    if(num%6!=1&&num%6!=5)return false;
    for(int i=5;i<=num/i;i+=6){
        if(num%i==0||num%(i+2)==0)return false;
    }
    return true;
}
void solve(void)
{
    int n;
    while(cin>>n){
        int cnt=0;
        while(n--){
            int x;cin>>x;
            if(isprime(x))cnt++;
        }
        cout<<cnt<<'\n';
    }
    return;
}
int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//solve();
    cout<<euler(2000000);
	return 0;
}
