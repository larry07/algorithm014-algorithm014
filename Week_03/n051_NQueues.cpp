
/**
好处理的一点:
逐行处理 索引就是行号，不需要矩阵存储
只需要一个数组 vector<int>
*/

class Solution {
    bool isValid(vector<int> & pos,int row,int col){//pos[row]=col
        for(int i=0;i<row;i++){		//[row][col]与 前row行的皇后位置检查
            if(pos[i]==col||
                (pos[i]+i==col+row)||
                (pos[i]-i==col-row))// 实际上就是x+y  x-y的截距一样
                return false;
        }
        return true;
    }

    void dfs(vector<vector<int> >& ans,vector<int> & pos,int row,const int n){//逐行放置 当前放row行 要放哪一列
        if(row==n){//放满了n行
            ans.push_back(pos);
            return;
        }
        for(int col=0;col<n;col++){//n列
            if(isValid(pos,row,col)){ // line[col]=1; 意义不同  pos存每一行皇后的位置，不需要二维数组!!
                pos[row]=col;
                dfs(ans,pos,row+1,n);
                pos[row]=0;
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        //求n个坐标 距离差>7  后面发现此题测试不考虑8以上的 7这一限制就不需要了
		//一定在不同行! 不用pair 按顺序即可
        vector<vector<int> >ans;
        vector<int> pos(n,0);		//代表二维矩阵，每一行皇后的位置  可用位代替

        dfs(ans,pos,0,n);

        //draw
        vector<vector<string>> res;

        for(auto vec:ans){
            vector<string> sol;
            for(int row=0;row<n;row++){
                string rowStr(n,'.');
                rowStr[vec[row]]='Q';
                sol.push_back(rowStr);
            }
            res.push_back(sol);
        }
        return res;
    }
};