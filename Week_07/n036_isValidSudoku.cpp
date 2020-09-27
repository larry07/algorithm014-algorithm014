
//有效的数独
//使用 行 列 块 数组，如果数值有出现，就将对应位置1，如果又遇到需要置1，就说明有冲突

//注意：board[i][j]-'0'-1 ;blkIdx=i/3*3+j/3;
//使用新看到的bitset<9> 除了内存小点，时间上好像还不如
//		int rows[9][9] = { 0 };
//      int cols[9][9] = { 0 };
//      int boxes[9][9] = { 0 };
		
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bitset<9> rows[9],cols[9],blocks[9];
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]=='.')continue;
                int v=board[i][j]-'0'-1,blkIdx=i/3*3+j/3;
                if(rows[i].test(v)||cols[j].test(v)||blocks[blkIdx].test(v))
                    return false;
                rows[i].set(v);
                cols[j].set(v);
                blocks[blkIdx].set(v);
            }
        }
        return true;
    }
};