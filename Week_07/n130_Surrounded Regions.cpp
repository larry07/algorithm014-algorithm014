
//130被包围的区域
//找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充
//任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'

//思路 从边界（外框）的'O'开始dfs，找到相连区域后后标记，即从目标区域  排除
//用'X'填充目标，同时还原 原'O'
class Solution {
    int n=0;
    int m=0;
	void dfs(vector<vector<char>>& board,int x,int y){
		if(board[x][y]!='O')return;

		board[x][y] = '#';  //'O'->'#' 则不会重复访问！
		if(x>0)dfs(board,x-1,y);
		if(y>0)dfs(board,x,y-1);
		if(x+1<n)dfs(board,x+1,y);
		if(y+1<m)dfs(board,x,y+1);
	}
public:
    void solve(vector<vector<char>>& board) {
        if(board.size()<=2||board[0].size()<=2)return; //隐含的条件 长宽<=2则  无需修改
        
        n = board.size(),m=board[0].size();
        for(int j=0;j<m;j++){
            dfs(board,  0,j);
            dfs(board,n-1,j);
        }
        for(int i=1;i<n-1;i++){
            dfs(board,i,  0);
            dfs(board,i,m-1);
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[i][j]=='#')
                    board[i][j] = 'O';
                else if(board[i][j]=='O')
                    board[i][j]='X';
            }
        }
    }
};