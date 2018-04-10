//
// Created by cjn on 2018/4/10.
//

#ifndef ALGS_SEGMENTTREE_H
#define ALGS_SEGMENTTREE_H

#include <vector>

class SegmentTree {
public:
    class SegmentTreeNode{
    public:
        int start_,end_,max_;
        SegmentTreeNode *left_,*right_;
        SegmentTreeNode(int start,int end,int max);
    };
    explicit SegmentTree(std::vector<int> nums);
    static SegmentTreeNode* Build(int left,int right,std::vector<int> nums);
    static void Modify(SegmentTreeNode* root, int index, int value);

    SegmentTreeNode* root_;

};


#endif //ALGS_SEGMENTTREE_H
