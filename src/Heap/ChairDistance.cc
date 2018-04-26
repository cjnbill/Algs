//
// Created by cjn on 2018/4/17.
//
#include <vector>
#include <queue>
#include <iostream>

struct cmp{
    bool operator()(std::pair<int,int> p1,std::pair<int,int> p2){
        return p1.second-p1.first<p2.second-p2.first;
    }
};
static int Sit(std::vector<int>& nums){
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,cmp> pq;
    int n=nums.size();
    int start=-1;
    for(int i=0;i<n;i++){
        if(i>0&&nums[i]==0&&nums[i-1]==1){
            start=i;
        }
        if(i+1<n&&nums[i]==0&&nums[i+1]==1){
            if(start!=-1)
                pq.push({start,i});
        }
    }
    auto p=pq.top();
    return (p.first+p.second)/2;
}
static std::vector<int> FollowUp(std::vector<int>& nums,int k){
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,cmp> pq;
    int n=nums.size();
    int start=-1;
    for(int i=0;i<n;i++){
        if(i>0&&nums[i]==0&&nums[i-1]==1){
            start=i;
        }
        if(i+1<n&&nums[i]==0&&nums[i+1]==1){
            if(start!=-1)
                pq.push({start,i});
        }
    }
    std::vector<int> res;
    while(k--){
        if(pq.empty())
            return res;
        auto t=pq.top();pq.pop();
        int m=(t.second+t.first)/2;
        res.push_back(m);
        if(m-1>=t.first)
            pq.push({t.first,m-1});
        if(m+1<=t.second)
            pq.push({m+1,t.second});
    }
    return res;
}