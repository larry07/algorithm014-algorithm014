
//多少个朋友圈
//并查集做法  模板
class UF{
private:
    int count;			//连通分量数目
    vector<int> parent;//父节点
    vector<int> rank;  //非严格的树高level
public:
    UF(int n){
        count=n;
        parent.resize(n);
        rank.resize(n);
        for(int i=0;i<n;++i){
            parent[i]=i;//指向本身
            //rank[i]=1; //默认0也可以
        }
    }
    int find(int x){//找根节点
        if(x!=parent[x]){
            parent[x] = find(parent[x]);       //递归版本 所有深度为1
        }
        return parent[x];;
    }
	
    void Union(int p,int q){//连通节点p和节点q
        int rootP=find(p);
        int rootQ=find(q);
        if(rootP==rootQ) return ;
		
        if(rank[rootP]<rank[rootQ]){//维持 lv rootP ≥rootQ
			swap(rootP,rootQ);
        }
        parent[rootQ]=rootP;
		if(rank[rootP]==rank[rootQ])rank[rootP]++;

        count--;//连通分量数目减1
    }
    bool Connected(int p,int q){//节点p和节点q是否连通
        int rootP=find(p);
        int rootQ=find(q);
        return rootP==rootQ;
    }
    int get_count()const{
        return count;
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if(M.size()==0) return 0;
        int N=M.size();
        UF* uf=new UF(N);
        for(int i=0;i<N;++i)
            for(int j=0;j<i;++j)
                if(M[i][j])
                    uf->Union(i,j);
        return uf->get_count(); 
    }
};

