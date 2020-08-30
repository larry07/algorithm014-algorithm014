/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 /**
 递归  从中序 知道当前根节点=>再从前序得到分割的区间，进行分治
 存 中序 <值-索引>关系，从前序构造
 */
class Solution {
    int maxVal=INT_MIN;
    inline int index(int val) {    /* return a node value's index on nodeMap */
        return (val >= 0 ? val : maxVal - val);
    }
	
    TreeNode* build(const vector<int>& preorder,int pl,int pr,int il,int* nodeMap){//[pl pr)
        if(pl==pr)
            return NULL;

        int rootVal = preorder[pl];
        TreeNode* root = new TreeNode(rootVal);

        int rootIndex = nodeMap[index(rootVal)];

        int delta = rootIndex - il;
        root->left = build(preorder,pl + 1, pl + delta + 1, il,nodeMap);
        root->right = build(preorder,pl + delta + 1, pr, rootIndex + 1, nodeMap);//[rootIndex+1 ..new rootIndex 绝对索引

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        int m = inorder.size();
        if(n == 0 && m == 0) return NULL;

        int minVal=INT_MAX;
        for(auto x:inorder){
            minVal = min(minVal,x);
            maxVal = max(maxVal,x);
        }
        int* nodeMap = new int[minVal>=0? maxVal+1: maxVal-minVal+1]; //构建哈希表
        for (int i = 0; i < m; i++) {
            nodeMap[index(inorder[i])] = i;
        }
        return build(preorder, 0, n, 0, nodeMap);
    }
};
/**
迭代法 巧妙的。。。
对于前序遍历中的任意两个连续节点 u 和 v，(u=>v=> )只可能有两种关系：
1.v 是 u 的左儿子。因为在遍历到 u 之后，下一个遍历的节点就是 u 的左儿子，即 v；
2.u 没有左儿子，并且 v 是 u 的某个祖先节点（或者 u 本身）的右儿子。
如果 u 没有左儿子，那么下一个遍历的节点就是 u 的右儿子。
如果 u 没有右儿子，就会向上回溯，直到遇到第一个有右儿子（且 u 不在它的右儿子的子树中）的节点 u_a，
那么 v 就是 u_a的右儿子。

栈：存当前节点的所有还没有考虑过右儿子的祖先节点，栈顶就是当前节点。初始为前序遍历的第一个节点。
index 指向中序遍历的某个位置，初值0。对应节点是「当前节点不断往左走达到的最终节点」

依次枚举 "前序遍历" 中除了第一个节点以外的每个节点。
如果 index 恰好指向栈顶节点，那么我们不断地弹出栈顶节点并向右移动 index，并将当前节点作为最后一个弹出的节点的右儿子；
如果 index 和栈顶节点不同，我们将当前节点作为栈顶节点的左儿子；

无论是哪一种情况，最后都将当前的节点入栈。
最后得到的二叉树即为答案。
*/

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};
