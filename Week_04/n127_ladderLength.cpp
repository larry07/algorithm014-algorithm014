

//单词接龙1

class Solution {
    //相同长度
    int dif(string& s1,string& s2){
        int n =s1.size(),cnt=0;
        for(int i=0;i<n;i++){
            if(s1[i]!=s2[i]){
                if(++cnt>1)break;
            }
        }
        return cnt;//0 1 2
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //BFS
        int n =wordList.size();
        vector<bool> vis(n,false);
        int len=1;
        
        queue<string> Q;
        Q.push(beginWord);
        while(!Q.empty()){
            int sz = Q.size();
            for(int i=0;i<sz;i++){
                string t =Q.front();Q.pop();
                if(t==endWord)return len;
                for(int j =0;j<n;j++){
                    if(dif(t,wordList[j])==1 && !vis[j]){
                        Q.push(wordList[j]);
                        vis[j]=true;
                    }
                }
            }
            len++;
        }
        return 0;
    }
};