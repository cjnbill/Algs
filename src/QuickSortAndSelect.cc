//
// Created by cjn on 2018/4/13.
//
#include <vector>
#include <algorithm>

//After partition, left side is bigger than pivot, right side is smaller than pivot
//return the position of pivot
static int Partition(std::vector<int>& nums,int left,int right){
    int l=left,r=right,pivot=nums[l];
    while(l<=r){
        if(nums[l]<pivot&&nums[r]>pivot)
            std::swap(nums[l++], nums[r--]);
        if(nums[l]>=pivot)
            l++;
        if(nums[r]<=pivot)
            r--;
    }
    std::swap(nums[left],nums[r]);
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