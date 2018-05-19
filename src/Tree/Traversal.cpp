//
// Created by cjn on 2018/5/18.
//

#include <printf.h>

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

void inorderMorrisTraversal(TreeNode *root) {
    TreeNode *cur = root, *prev = NULL;
    while (cur != NULL)
    {
        if (cur->left == NULL)          // 1.
        {
            printf("%d ", cur->val);
            cur = cur->right;
        }
        else
        {
            // find predecessor
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur)
                prev = prev->right;

            if (prev->right == NULL)   // 2.a)
            {
                prev->right = cur;
                cur = cur->left;
            }
            else                       // 2.b)
            {
                prev->right = NULL;
                printf("%d ", cur->val);
                cur = cur->right;
            }
        }
    }
}


void preorderMorrisTraversal(TreeNode *root) {
    TreeNode *cur = root, *prev = NULL;
    while (cur != NULL)
    {
        if (cur->left == NULL)
        {
            printf("%d ", cur->val);
            cur = cur->right;
        }
        else
        {
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur)
                prev = prev->right;

            if (prev->right == NULL)
            {
                printf("%d ", cur->val);  // the only difference with inorder-traversal
                prev->right = cur;
                cur = cur->left;
            }
            else
            {
                prev->right = NULL;
                cur = cur->right;
            }
        }
    }
}