
相比N皇后II  这里需要打印棋盘 需要位置信息，所以位运算是有点难做的
有以下2种方法
(1)使用 __builtin_ctz  返回后面0的个数  也就是当前bit 是哪一位
(2)使用对数函数 log2 也很方便

class Solution {
    vector<vector<string>> result;
    vector<int> queens;

    vector<string> generateBoard(vector<int> &queens, int n) {
        auto board = vector<string>();
        for (int i = 0; i < n; i++) {
            string row = string(n, '.');
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }

//按行 row 进行 dfs
    void dfs(int n,int row,int col,int ld,int rd){
        if(row>=n){
            result.emplace_back(generateBoard(queens,n));
            return;
        }
        int bits = ~(col|ld|rd) &((1<<n)-1);
        while(bits){
            int pick =bits&-bits;
            queens[row] = __builtin_ctz(pick);
            dfs(n,row+1,col|pick,(ld|pick)<<1,(rd|pick)>>1);
            bits &= bits-1;
            queens[row]=-1;
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        queens.resize(n);
        dfs(n,0,0,0,0);
        return result;
    }
};

//直接赋值最后需要的图形
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        if (n <= 0) return result;
        size = (1 << n) - 1;
        vector<string> nQueens(n, string(n, '.'));
        solve(nQueens, n, 0, 0, 0, 0);
        return result;
    }
    void solve(vector<string>& nQueens, int n, int row, int col, int ld, int rd) {
        if (row >= n) {
            result.push_back(nQueens);
            return ;
        }

        int bits = size & (~(col | ld | rd));
        while (bits != 0) {
            int bit = bits & (-bits);
            bits &= (bits - 1);
            // 计算第几位是1，用对数函数log2十分方便
            nQueens[row][log2(bit)] = 'Q';
            solve(nQueens, n, row + 1, col | bit, (ld | bit) << 1, (rd | bit) >> 1);
            nQueens[row][log2(bit)] = '.';
        }
    }
private:
    int size;
    vector<vector<string>> result;
};
