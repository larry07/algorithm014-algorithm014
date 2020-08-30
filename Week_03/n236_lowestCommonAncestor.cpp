/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//递归 后序遍历
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL||root==p||root==q)return root; //到p q 就不再下探了
        
        TreeNode*left = lowestCommonAncestor(root->left,p,q);   //如果能经过p q 则会返回p q 的
        TreeNode*right = lowestCommonAncestor(root->right,p,q); //全经过之后 才得到的这个left right
        // if(left==NULL && right==NULL)
        //     return NULL;

        if(left==NULL)
            return right;
        if(right==NULL)
            return left;
        return root;
    }
};

/*
存储父节点方法:

从根节点开始遍历整棵二叉树，用哈希表记录每个节点的父节点指针。
从 p 节点开始不断往它的祖先移动，并用数据结构记录已经访问过的祖先节点。
同样，我们再从 q 节点开始不断往它的祖先移动，如果有祖先已经被访问过，即意味着这是 p 和 q 的深度最深的公共祖先，即 LCA 节点。
*/
class Solution {
public:
    unordered_map<int, TreeNode*> fa;
    unordered_map<int, bool> vis;
    void dfs(TreeNode* root){
        if (root->left != nullptr) {
            fa[root->left->val] = root; //记录 左节点的父亲
            dfs(root->left);
        }
        if (root->right != nullptr) {
            fa[root->right->val] = root;//记录 右节点的父亲
            dfs(root->right);
        }
    }
	
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        fa[root->val] = nullptr;
        dfs(root);
        while (p != nullptr) {
            vis[p->val] = true;
            p = fa[p->val];     //向上移动	先把 p 祖先 访问一遍
        }
        while (q != nullptr) {
            if (vis[q->val]) return q;
            q = fa[q->val];
        }
        return nullptr;
    }
};
