vector<long long>b;
int li(long long x){
    return (int)(lower_bound(b.begin(),b.end(),x)-b.begin()+1);
}
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
