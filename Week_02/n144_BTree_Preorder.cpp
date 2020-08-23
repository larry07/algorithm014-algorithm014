

class Solution {
    void _preorderTraversal(vector<int>& v,TreeNode* root){
        if(root==NULL)
            return;
        v.push_back(root->val);
        _preorderTraversal(v,root->left);
        _preorderTraversal(v,root->right);
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        _preorderTraversal(res,root);
        return res;
    }
};


//同589 的N叉树  前序遍历    模拟栈
vector<int> preorder(Node* root) {
    if(!root) return {};
    stack<Node*> S;
    vector<int> res;
    S.push(root);
    
    while(!S.empty()){
        auto cur = S.top();
        S.pop();
        res.push_back(cur->val);
        for(int i = cur->children.size() - 1;  i >= 0 ; i--){
            if(cur->children[i]) S.push(cur->children[i]);
        }
    }
    return res;
}

//线索二叉树  莫里斯遍历 还未做


