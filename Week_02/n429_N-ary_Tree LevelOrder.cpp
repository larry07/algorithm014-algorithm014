
//dfs+传入level信息
class Solution {
    vector<vector<int> > res;
    void dfs(Node* node,int level){
        if(res.size()<=level)
			res.emplace_back(vector<int>());//还没有加入本level数组
        res[level].emplace_back(node->val);
        for(auto x:node->children){
            if(x)dfs(x,level+1);
        }
    }
public:
    vector<vector<int>> levelOrder(Node* root) {
        if(root==NULL) return {};
        dfs(root,0);
        return res;
    }
};

//bfs+队列
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if(root==NULL) return {};
        vector<vector<int>> res;
        deque<Node*> dq;
        dq.push_back(root);
        Node* t = NULL;
        int len;
        while(!dq.empty()){
            int sz=dq.size();
            vector<int> cur;
            for(int i = 0;i<sz;i++){
                t = dq.front();
                cur.push_back(t->val);
                dq.pop_front();
                len=t->children.size();
                for(int j=0;j<len;j++){
                    if(t->children[j])dq.push_back(t->children[j]);
                }
            }
            res.emplace_back(cur);
        }
        return res;
    }
};