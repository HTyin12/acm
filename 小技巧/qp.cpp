long long qp(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1){
			ans=a*ans%mod;	
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

//¿ìËÙ³Ë

long long mul(long long a,long long b) 
{
    long long ans=0;
    a%=mod,b%=mod;
    while(b){
        if(b&1){
            ans=(ans+a)%mod;
        }
        a<<=1;a%=mod;
        b>>=1;
    }
    return ans;
}
long long qp(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1){
			ans=mul(ans,a);	
		}
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}
