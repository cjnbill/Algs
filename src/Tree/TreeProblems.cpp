//
// Created by cjn on 2018/5/8.
//

#include <vector>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
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

