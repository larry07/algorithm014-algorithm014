/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

//栈模拟  从后往前压栈
class Solution {
public:
    vector<int> preorder(Node* root) {
        if(root==NULL)return {};
        vector<int> res;
        stack<Node*> Q;
        Q.push(root);
        
        Node* cur;
        while(!Q.empty()){
            cur=Q.top();
            Q.pop();
            res.push_back(cur->val);
            for(int i= cur->children.size()-1;i>=0;i--){
                if(cur->children[i])Q.push(cur->children[i]);
            }
        }
        return res;
    }
};

//普通递归
class Solution {
    void _preorder(vector<int>& vec,Node* root) {
        if(root==NULL)return;
        vec.push_back(root->val);
        for(auto node:root->children){
            if(node!=NULL)_preorder(vec,node);
        }
    }
public:
    vector<int> preorder(Node* root) {
        vector<int> res;
        _preorder(res,root);
        return res;
    }
};