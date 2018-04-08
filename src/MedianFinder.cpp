//
// Created by cjn on 2018/4/7.
//
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
class MedianFinder {
public:
    /** initialize your data structure here. */
    double median;
    bool isEmpty;
    priority_queue<double,vector<double>> maxheap;
    priority_queue<double,vector<double>,greater<double>> minheap;
    MedianFinder():isEmpty(true),median(){}

    void addNum(int num) {
        //cout<<num<<" "<<median<<endl;
        if(isEmpty){
            median=num;
            isEmpty=false;
            return;
        }
        if(num<median){
            maxheap.push(num);
            //unbalance:left==right+1
            if(maxheap.size()==minheap.size()+1){
                auto t=maxheap.top();maxheap.pop();
                minheap.push(median);
                median=t;
            }
        }
        else{
            minheap.push(num);
            //unbalance: right=left+2
            if(minheap.size()==maxheap.size()+2){
                auto t=minheap.top();minheap.pop();
                maxheap.push(median);
                median=t;
            }
        }
    }

    double findMedian() {
        if(maxheap.size()==minheap.size())
            return median;
        else return (minheap.top()+median)/2;
    }
};


vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    auto n=nums.size();
    multiset<int> lo;
    multiset<int> hi;
    vector<double> res;

    for(int i=0;i<n;i++){
        //delete left side of the window
        if(i>=k){
            if(lo.count(nums[i-k])){
                lo.erase(lo.find(nums[i-k]));
            }
            else if(hi.count(nums[i-k])){
                hi.erase(hi.find(nums[i-k]));
            }
        }
        //add the right side
        lo.insert(nums[i]);
        hi.insert(*lo.begin());
        lo.erase(lo.begin());
        if(lo.size()<hi.size()){
            lo.insert(*hi.rbegin());
            hi.erase(--hi.end());
        }
        if(i>=k-1){
            if(hi.size()<lo.size()){
                res.push_back(*lo.begin());
            }
            else res.push_back(((double)*lo.begin()+*hi.rbegin())/2.0);
        }
    }
    return res;
}