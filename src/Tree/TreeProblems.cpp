//
// Created by cjn on 2018/5/8.
//

#include <vector>
#include <stack>
#include <string>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v):val(v){}
};
static bool similar(TreeNode* root1, TreeNode* root2){
        if(root1 == nullptr && root2 == nullptr) return true;

        if(root1 != nullptr && root2 != nullptr && root1 -> val == root2 -> val) {
                return (similar(root1->left, root2->left) &&  similar(root1->right, root2->right)) ||
                (similar(root1->left, root2->right) && similar(root1->right, root2-> left));
        }

        return false;
}


vector<int> preorderTraversal(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    stack<TreeNode*> s{{root}};
    while (!s.empty()) {
        TreeNode *t = s.top(); s.pop();
        res.push_back(t->val);
        if (t->right) s.push(t->right);
        if (t->left) s.push(t->left);
    }
    return res;
}

vector<int> inorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (p || !s.empty()) {
        while (p) {
            s.push(p);
            p = p->left;
        }
        p = s.top();
        s.pop();
        res.push_back(p->val);
        p = p->right;
    }
    return res;
}

vector<int> postorderTraversal(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    stack<TreeNode*> s{{root}};
    while (!s.empty()) {
        TreeNode *t = s.top(); s.pop();
        res.insert(res.begin(), t->val);
        if (t->left) s.push(t->left);
        if (t->right) s.push(t->right);
    }
    return res;
}

class KthBST {
public:
    int kthSmallest(TreeNode* root, int k) {
        int cnt = count(root->left);
        if (k <= cnt) {
            return kthSmallest(root->left, k);
        } else if (k > cnt + 1) {
            return kthSmallest(root->right, k - cnt - 1);
        }
        return root->val;
    }
    int count(TreeNode* node) {
        if (!node) return 0;
        return 1 + count(node->left) + count(node->right);
    }
};

//543. Diameter of Binary Tree
int depth(TreeNode* node,int& res){
    if(!node)
        return 0;
    int l=depth(node->left,res),r=depth(node->right,res);
    res=max(res,l+r);
    return max(l,r)+1;
}

int diameterOfBinaryTree(TreeNode* root) {
    int res=0;
    depth(root,res);
    return res;
}

//549. Binary Tree Longest Consecutive Sequence II
class LongestConsecutive {
public:
    int longestConsecutive(TreeNode* root) {
        int res=0;
        helper(res,root);
        return res;
    }
    pair<int,int> helper(int& res,TreeNode* node){
        if(!node){
            return {0,0};
        }
        auto l=helper(res,node->left);
        auto r=helper(res,node->right);
        int inc=1,dec=1;
        if(node->left){
            if(node->val==node->left->val+1){
                inc=max(inc,l.first+1);
            }
            if(node->val==node->left->val-1){
                dec=max(dec,l.second+1);
            }
        }

        if(node->right){
            if(node->val==node->right->val+1){
                inc=max(inc,r.first+1);
            }
            if(node->val==node->right->val-1){
                dec=max(dec,r.second+1);
            }
        }
        res=max(res,inc+dec-1);

        return {inc,dec};
    }
};

//297. Serialize and Deserialize Binary Tree
//序列化用先序遍历
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "#";
        return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return mydeserialize(data);
    }
    TreeNode* mydeserialize(string& data) {
        if (data[0]=='#') {
            if(data.size() > 1) data = data.substr(2);
            return nullptr;
        } else {
            TreeNode* node = new TreeNode(helper(data));
            node->left = mydeserialize(data);
            node->right = mydeserialize(data);
            return node;
        }
    }
private:
    int helper(string& data) {
        int pos = data.find(',');
        int val = stoi(data.substr(0,pos));
        data = data.substr(pos+1);
        return val;
    }
};
