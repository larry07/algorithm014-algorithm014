


//左 根 右  递归
class Solution {
    void _inorderTraversal(vector<int>& v,TreeNode* root){
        if(root==NULL)
            return;
        _inorderTraversal(v,root->left);
        v.push_back(root->val);
        _inorderTraversal(v,root->right);
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        _inorderTraversal(res,root);
        return res;
    }
};


//模拟栈
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while(cur!=NULL || !st.empty()){
            while(cur!=NULL){ //一直向左走 直到无左子树
                st.push(cur);
                cur=cur->left;
            }
            cur = st.top();
            st.pop();
            res.push_back(cur->val);   //do
            cur=cur->right;            //右子树
        }
        return res;
    }
};

