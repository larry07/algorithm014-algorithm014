
/**
208.前缀树实现
*/

//实现1 模板 主要是记住2个方法 insert 和 find (拓展出search是精确查找,startWith是模糊)
//Trie持有一个root来管理整棵树
class Trie {
    struct TrieNode{
        bool isEnd;
        unordered_map<char,TrieNode*> nextMap;//内存上可能不如Trie* next[26];但不是固定26叉
        TrieNode():isEnd(0){}
    };
private:
    TrieNode* root;
    bool find(string word,bool exact_match){
        TrieNode* p = root;
        for(char c:word){
            if(p->nextMap.count(c)==0)
                return false;
            p=p->nextMap[c];
        }
        if(exact_match)
            return p->isEnd?true:false;
        return true;
    }
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* p = root;
        for(char c:word){
            if(p->nextMap.count(c)==0)
                p->nextMap[c] = new TrieNode();
            p=p->nextMap[c];
        }
        p->isEnd = 1;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        return find(word,1);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return find(prefix,0);
    }
};

//实现2
class Trie {
private:
    bool isEnd;
    Trie* next[26]{}; //独立的TrieNode结点更好，因为少了几个函数指针
public:
    /** Initialize your data structure here. */
    Trie() {
        isEnd=false;
        memset(next,0,26);
    }
    ~Trie(){
        for(int i=0;i<26;i++){
            if(next[i]==nullptr)continue;
            delete next[i];
            next[i] = nullptr;
        }
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* cur = this;
        for(char c:word){
            if(cur->next[c-'a']==nullptr)
                cur->next[c-'a']=new Trie();
            cur = cur->next[c-'a'];
        }
        cur->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* cur = this;
        for(char c:word){
            if(cur->next[c-'a']==nullptr)
                return false;
            cur = cur->next[c-'a'];
        }
        return cur->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* cur = this;
        for(char c:prefix){
            if(cur->next[c-'a']==nullptr)
                return false;
            cur = cur->next[c-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */