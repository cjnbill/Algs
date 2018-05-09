//
// Created by cjn on 2018/5/8.
//

struct node{
    int val;
    node* left;
    node* right;
};
static bool similar(node* root1, node* root2){
        if(root1 == nullptr && root2 == nullptr) return true;

        if(root1 != nullptr && root2 != nullptr && root1 -> val == root2 -> val) {
                return (similar(root1->left, root2->left) &&  similar(root1->right, root2->right)) ||
                (similar(root1->left, root2->right) && similar(root1->right, root2-> left));
        }

        return false;
}