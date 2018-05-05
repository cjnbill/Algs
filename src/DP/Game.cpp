//
// Created by cjn on 2018/4/26.
//
#include <vector>
#include <iostream>
using namespace std;

//486. Predict the Winner
//dp[i][j] is the max score for interval from index i to j
//         1.pick the left ,then chose min from next round
//         2.pick the right, then chose min from next round
bool PredictTheWinner(vector<int>& nums) {
    int n=nums.size();
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int i=0;i<n;i++)
        dp[i][i]=nums[i];
    for(int i=0;i<n-1;i++)
        dp[i][i+1]=max(nums[i],nums[i+1]);
    for(int len=3;len<=n;len++){
        for(int i=0;i+len-1<n;i++){
            int j=i+len-1;
            int left_res=nums[i]+min(dp[i+1][j-1],dp[i+2][j]);
            int right_res=nums[j]+min(dp[i][j-2],dp[i+1][j-1]);
            dp[i][j]=max(left_res,right_res);
            cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
        }
    }
    int sum=0;
    for(auto num:nums)
        sum+=num;
    //cout<<dp[0][n-1]<<" "<<sum<<endl;
    return dp[0][n-1]>=(sum-dp[0][n-1]);
}