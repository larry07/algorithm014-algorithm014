
//22括号生成
//dp[i]={"("+dp[left]+")"+dp[right]}  其中left+right=i-1

vector<string> generateParenthesis(int n) {
    if (n == 0) return {};
    if (n == 1) return { "()" };
    vector<vector<string>> dp(n+1);
    dp[0]={""};
    dp[1]={"()"};
    for(int i=2;i<=n;i++){//dp[i] l+r=i-1
        for(int l=0;l<i;l++){
            for(string& left:dp[l]){
                for(string& right:dp[i-1-l]){
                    dp[i].emplace_back("("+left+")"+right);
                }
            }
        }
    }
    return dp[n];
}


//常规回溯
vector<string> res;
void bt(string s,int l,int r,int n){
	if(s.size()==2*n){
		res.emplace_back(s);
		return;
	}
	if(l<n)
		bt(s+'(',l+1,r,n);
	if(l>r)    // && r<n  => r<l<=n   剪枝
		bt(s+')',l,r+1,n);
}

vector<string> generateParenthesis(int n) {
	bt("",0,0,n);
	return res;
}