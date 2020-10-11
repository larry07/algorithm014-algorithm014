

//最简 位运算
//bits得到所有可用空位  &((1<<n)-1)是为了保证位宽为n
//
class Solution {
    int cnt=0;
    void dfs(int n,int row,int col,int ld,int rd){
        if(row>=n){
            cnt++;return;
        }
        int bits=~(col|ld|rd) &((1<<n)-1);
        while(bits){
            int pick = bits&-bits;		// 注: x & -x     取到最低位的1  选一个可用空位
            bits&=(bits-1);				// 注: x & (x - 1)移除最右边位的1
            dfs(n,row+1,col|pick,(ld|pick)<<1,(rd|pick)>>1);
        }
    }
public:
    int totalNQueens(int n) {
        dfs(n,0,0,0,0);
        return cnt;
    }
};