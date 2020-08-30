class Solution {
    vector<vector<int>> ans;
    vector<int> list;

    void dfs(int n, int k, int start){
		// if(start==k+1){//start 不能同时作为list计数!
        if(list.size()==k){
            ans.push_back(list);
            return;
        }

        for(int i=start;i<=n+1-(k- list.size());i++){
            //if(list.empty()||i>list.back()){//放入的时候就能剪枝
                list.push_back(i);
                dfs(n,k,i+1);		//i+1即可有序 而不是 start+1
                list.pop_back();  
            //}    
        }
/*		传入i (=start)
		if (vec.size() + n - i + 1 < k) return;
        dfs(res, vec, n, i + 1, k);  //不选择当前
		
        vec.push_back(i);
        dfs(res, vec, n, i + 1, k); //选择当前！
        vec.pop_back();
*/
    }
public:
    vector<vector<int>> combine(int n, int k) {
        if (n <= 0 || k <= 0 || k > n) {
            return ans;
        }
        dfs(n,k,1);
        return ans;
    }
};

/*
字典序解法
*/
vector<vector<int>> combine(int n, int k) {
	vector<vector<int> > res;
	vector<int> list;
	for (int i = 1; i < k+1; ++i)
		list.emplace_back(i);
	list.emplace_back(n+1);
	int j=0;
	while(j<k){
		res.emplace_back(list.begin(),list.begin()+k);
		j=0;
		while((j<k) && list[j]+1==list[j+1]) {//到达本位最高1011 =>1100
			list[j] = j + 1;				  //(还原)正常的[0]=1
			j++;
		}
		list[j]=list[j]+1;
		for(auto x:list)
			cout<<x<<" ";
		cout<<endl;
	}
	return res;
}