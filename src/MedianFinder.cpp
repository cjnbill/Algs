//
// Created by cjn on 2018/4/7.
//
#include <iostream>
#include <vector>
#include <queue>

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

