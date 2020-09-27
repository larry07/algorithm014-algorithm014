
//岛屿数量  每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。
//用DFS解了
class Solution {
    int N,M;
    void dfs(vector<vector<char>>& grid,int r,int c){
        if(grid[r][c]!='1')  //陆地
            return;
        grid[r][c] = '2';
        if(r>0)dfs(grid,r-1,c);
        if(r<N-1)dfs(grid,r+1,c);
        if(c>0)dfs(grid,r,c-1);
        if(c<M-1)dfs(grid,r,c+1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty())return 0;
        N = grid.size();
        M = grid[0].size();
        int cnt =0;

        for (int i = 0;i<N;i++){
            for(int j=0;j<M;j++){
                if(grid[i][j]=='1'){
                    dfs(grid,i,j);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};