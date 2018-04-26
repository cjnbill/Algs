//
// Created by cjn on 2018/4/13.
//
#include <vector>
#include <algorithm>

//After partition, left side is bigger than pivot, right side is smaller than pivot
//return the position of pivot
static int Partition(std::vector<int>& nums,int l,int r){
    int pivot=nums[l];
    while(l<r){
        while(l<r&&nums[r]>=pivot)
            r--;
        nums[l]=nums[r];
        while(l<r&&nums[l]<=pivot)
            l++;
        nums[r]=nums[l];
    }
    nums[l]=pivot;
    return r;
}

static int QuickSelect(std::vector<int>& nums,int k){
    int l=0,r=nums.size()-1;
    while(l<=r){
        int pos=Partition(nums,l,r);
        if(pos==k-1)
            return nums[pos];
        else if(pos<k-1)
            l=pos+1;
        else r=pos-1;
    }
    return 0;
}