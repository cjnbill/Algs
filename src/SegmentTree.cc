//
// Created by cjn on 2018/4/10.
//

#include "SegmentTree.h"

SegmentTree::SegmentTreeNode::SegmentTreeNode(int start,int end,int max):start_(start),end_(end),max_(max){
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
    auto root = new SegmentTreeNode(left,right,nums[left]);
    if(left==right)
        return root;
    int mid=(left+right)/2;
    root->left_=Build(left,mid,nums);
    root->right_=Build(mid+1,right,nums);
    root->max_=std::max(root->left_->max_,root->right_->max_);
    return root;
}

void SegmentTree::Modify(SegmentTreeNode* root, int index, int value){
    if(root->end_==root->start_&&root->start_==index) {
        root->max_ = value;
        return;
    }
    int mid=(root->start_+root->end_)/2;
    if(index<=mid){
        Modify(root->left_,index,value);
        root->max_=std::max(root->left_->max_,root->right_->max_);
    }
    else {
        Modify(root->right_, index, value);
        root->max_=std::max(root->right_->max_,root->left_->max_);
    }
}
