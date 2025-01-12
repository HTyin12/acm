struct node{
	int l, r;
	mutable long long v;
	node(int L,int R=-1,long long V=0) : l(L), r(R), v(V) {}
	bool operator<(const node &o) const { return l < o.l; }
};
set<node>odt;
auto split(int pos){
	auto it =odt.lower_bound(node(pos));
	if (it!=odt.end()&&it->l==pos) return it;
	--it;
	if(pos>it->r)return odt.end();
	int L=it->l,R=it->r;long long V=it->v;
	odt.erase(it);
	odt.insert(node(L, pos-1,V));
	return odt.insert(node(pos,R,V)).first;
}
//区间加 (区间模板)
void add(int l,int r,long long val=1){
	auto itr=split(r+1),itl=split(l);
	for(;itl!=itr;++itl)itl->v+=val;
}
//区间覆盖
void assign(int l,int r,long long val=0){
	auto itr=split(r+1),itl=split(l);
	odt.erase(itl,itr);
	odt.insert(node(l,r,val));
}
