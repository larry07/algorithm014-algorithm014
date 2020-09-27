
//单词搜索II
//主要是 预先 建立前缀树  然后进行DFS,能到达某个单词的End则说明找到了一个

class TrieNode{
public:
    string word = "";//代替了isEnd  可以直接知道是哪个单词
    vector<TrieNode*> nodes;
    TrieNode():nodes(26, 0){}
};

class Solution {
    int rows, cols;
    vector<string> res;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        rows = board.size();
        cols = rows ? board[0].size():0;
        if(rows==0 || cols==0) return res;

        //从已知 words 建立字典树  对每个词执行 插入字典树
        TrieNode* root = new TrieNode();
        for(string word:words){
            TrieNode *cur = root;
            for(char c:word){
                int idx = c-'a'; 
                if(cur->nodes[idx]==nullptr)
                    cur->nodes[idx] = new TrieNode();
                cur = cur->nodes[idx];
            }
            cur->word = word;
        }

        //DFS模板 
        for(int i=0; i<rows; ++i){
            for(int j=0; j<cols; ++j){
                dfs(board, root, i, j);
            }
        }
        return res;
    }

//仍是dfs网格，对比单词搜索1  word[index]!=board[x][y] 这里是看当前树结点的指针域 是否有效
    void dfs(vector<vector<char>>& board, TrieNode* root, int x, int y){
        char c = board[x][y];
        //递归边界
        if(c=='.' || root->nodes[c-'a']==nullptr) return;
        root = root->nodes[c-'a'];
        if(root->word!=""){
            res.push_back(root->word);
            root->word = "";
        }
        
        board[x][y] = '.';
        if(x>0) dfs(board, root, x-1, y);
        if(y>0) dfs(board, root, x, y-1);
        if(x+1<rows) dfs(board, root, x+1, y);
        if(y+1<cols) dfs(board, root, x, y+1);
        board[x][y] = c;
    }  
};
