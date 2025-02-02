int qp_oula(string &s){
        if(s.size()>=10||stoi(s)>=P-1){
            int m=0;for(auto i:s)m=(m*10+i-'0')%(P-1);
            return m+P-1;
        }else{
            return stoi(s);
        }
    }