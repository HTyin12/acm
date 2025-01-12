for(int i=1;i<=n;i++){
	while(!st.empty()&&date[st.top()]<date[i]){
		ans[st.top()]=i;
		st.pop();
	}
	st.push(i);
}
while(!st.empty()){
	ans[st.top()]=0;
	st.pop();
}