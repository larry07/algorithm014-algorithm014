/**
64. 最小路径和
m x n 网格，每次只能向下或者向右移动一步。请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 
dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
从左和上得到当前，没有左上，所以这里直接从左向右递推即可，不存在覆盖

压缩 使用n空间，就要单独处理  "无左" 和 "无上"
*/
int minPathSum(vector<vector<int>>& grid) {
	if(grid.empty()||grid[0].empty())return 0;

	int m =grid.size(),n=grid[0].size();
	vector<int> dp(n,0);
	dp[0]=grid[0][0];				//无左 无上
	for(int j=1;j<n;j++){
		dp[j]=dp[j-1]+grid[0][j];	//无上
	}
	
	for(int i=1;i<m;i++){
		dp[0]+=grid[i][0];			//每行开始  无左
		for(int j=1;j<n;j++)
			dp[j]=min(dp[j],dp[j-1])+grid[i][j];
	}
	return dp[n-1];
}