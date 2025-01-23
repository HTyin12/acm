auto calc=[&](int x){
	
};
auto find=[&](int l,int r){
	int L=l;
	while(l<r-1){
		int mid=(l+r)>>1;
		int mmid=(mid+r)>>1;
		if(calc(mid)>calc(mmid))r=mmid;
		else l=mid;
	}
	int res=calc(l)>calc(r)?l:r;
	return calc(L)>calc(res)?L:res;
};