//
// Created by cjn on 2018/4/10.
//

#include "SegmentTree.h"

SegmentTree::SegmentTreeNode::SegmentTreeNode(int start,int end,int sum):start_(start),end_(end),sum_(sum){
    left_= nullptr;
    right_= nullptr;
}

SegmentTree::SegmentTree(std::vector<int> nums) {
    root_ = Build(0,(int)nums.size()-1,nums);
}

SegmentTree::SegmentTreeNode* SegmentTree::Build(int left,int right,std::vector<int> nums){
    if(left>right){
        return nullptr;
    }
    auto root = new SegmentTreeNode(left,right,0);
    if(left==right)
        return root;
    int mid=(left+right)/2;
    root->left_=Build(left,mid,nums);
    root->right_=Build(mid+1,right,nums);
    if(root->left_)
        root->sum_+=root->left_->sum_;
    if(root->right_)
        root->sum_+=root->right_->sum_;
    return root;
}

void SegmentTree::Modify(SegmentTreeNode* root, int index, int value){
    if(root->end_==root->start_&&root->start_==index) {
        root->sum_ = value;
        return;
    }
    int mid=(root->start_+root->end_)/2;
    //note:<=
    if(index<=mid){
        Modify(root->left_,index,value);
        root->sum_=root->left_->sum_+root->right_->sum_;
    }
    else {
        Modify(root->right_, index, value);
        root->sum_=root->right_->sum_+root->left_->sum_;
    }
}

int SegmentTree::Query(SegmentTreeNode* root, int left, int right){
    if (!root)
        return 0;
    if(root->start_==left&&root->end_==right){
        return root->sum_;
    }
    int mid=root->start_+(root->start_-root->end_)/2;
    if(mid<left)
        return Query(root->right_,left,right);
    if(mid>=right)
        return Query(root->left_,left,right);
    return Query(root->left_,left,mid)+Query(root->right_,mid,right);
}
