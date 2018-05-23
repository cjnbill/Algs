//
// Created by cjn on 2018/5/20.
//

#include <vector>
#include <set>
using namespace std;

//480. Sliding Window Median
//use two multiset, left==right or left ==right +1

class MedianSlidingWindow {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n=nums.size();
        multiset<int> lo,hi;
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
            if(lo.size()+1<hi.size()){
                lo.insert(*hi.rbegin());
                hi.erase(--hi.end());
            }
            if(i>=k-1){
                double median;
                if(hi.size()>lo.size()){
                    res.push_back(*hi.rbegin());
                }
                else res.push_back(((double)*lo.begin()+*hi.rbegin())/2.0);
            }
        }
        return res;
    }
};
