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

// C++ program to print inorder traversal of a Binary Search
// Tree (BST) without recursion and stack

/*
 *
1. Initialize current node as root
2. Initialize a flag: leftdone = false;
3. Do following while root is not NULL
     a) If leftdone is false, set current node as leftmost
        child of node.
     b) Mark leftdone as true and print current node.
     c) If right child of current nodes exists, set current
        as right child and set leftdone as false.
     d) Else If parent exists, If current node is left child
        of its parent, set current node as parent.
        If current node is right child, keep moving to ancestors
        using parent pointer while current node is right child
        of its parent.
     e) Else break (We have reached back to root)
 */
// BST Node
struct Node
{
    Node *left, *right, *parent;
    int key;
};

// A utility function to create a new BST node
Node *newNode(int item)
{
    Node *temp = new Node;
    temp->key = item;
    temp->parent = temp->left = temp->right = NULL;
    return temp;
}

/* A utility function to insert a new node with
   given key in BST */
Node *insert(Node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
    {
        node->left  = insert(node->left, key);
        node->left->parent = node;
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
        node->right->parent = node;
    }

    /* return the (unchanged) node pointer */
    return node;
}

// Function to print inorder traversal using parent
// pointer
void inorder(Node *root)
{
    bool leftdone = false;

    // Start traversal from root
    while (root)
    {
        // If left child is not traversed, find the
        // leftmost child
        if (!leftdone)
        {
            while (root->left)
                root = root->left;
        }

        // Print root's data
        printf("%d ", root->key);

        // Mark left as done
        leftdone = true;

        // If right child exists
        if (root->right)
        {
            leftdone = false;
            root = root->right;
        }

            // If right child doesn't exist, move to parent
        else if (root->parent)
        {
            // If this node is right child of its parent,
            // visit parent's parent first
            while (root->parent &&
                   root == root->parent->right)
                root = root->parent;
            if (!root->parent)
                break;
            root = root->parent;
        }
        else break;
    }
}