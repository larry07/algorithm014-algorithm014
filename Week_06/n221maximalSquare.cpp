//最大正方形  [i,j]作为右下角的最大正方形宽度
//伪代码：dp(i, j) = min(dp(i - 1, j), dp(i, j - 1), dp(i - 1, j - 1)) + 1;
//因为 当前要想组成正方形，三者必须都有那个宽度，所以最大就是三者的最小值
//状态压缩
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()||matrix[0].empty()) return 0;
        int n = matrix.size(),m=matrix[0].size();
        int maxWidth=0;

        vector<int> dp(m+1,0);
        int leftUp,up;			//左上 和 上
        for(int i=0;i<n;i++){
            leftUp=0;			//!!!重要，因为遍历一行后，leftUp为最后一个，新一行需要清掉
            for(int j=0;j<m;j++){
                up=dp[j+1];		//保存未赋值前的 上
                if(matrix[i][j]=='0'){
                    dp[j+1] = 0;
                }else{
                    dp[j+1]=min(min(dp[j],up),leftUp)+1;
                }
                leftUp=up;		//左上向右移
                maxWidth = max(maxWidth,dp[j+1]);
            }
        }
        return maxWidth*maxWidth;
    }
};