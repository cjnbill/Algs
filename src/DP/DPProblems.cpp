//
// Created by cjn on 2018/5/16.
//

#include <vector>
#include <iostream>
using namespace std;

//486. Predict the Winner
//dp[i][j] is the max score for interval from index i to j
//         1.pick the left ,then chose min from next round
//         2.pick the right, then chose min from next round
static bool PredictTheWinner(vector<int>& nums) {
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


//552. Student Attendance Record II

//P[i] = A[i-1] + P[i-1] + L[i-1]
//L[i] = A[i-1] + P[i-1] + A[i-2] + P[i-2]
//A[i] = noAP[i-1] +noAL[i-1]
//noAP[i] =  noAP[i-1] + noAL[i-1]
//noAL[i] =  noAP[i-1] + noAP[i-2]
//A[i] = A[i-1] + A[i-2] + A[i-3]

static int checkRecord(int n) {
    int M = 1000000007;
    vector<int> P(n), L(n), A(n);
    P[0] = 1; L[0] = 1; L[1] = 3;
    A[0] = 1; A[1] = 2; A[2] = 4;
    for (int i = 1; i < n; ++i) {
        P[i] = ((P[i - 1] + L[i - 1]) % M + A[i - 1]) % M;
        if (i > 1) L[i] = ((A[i - 1] + P[i - 1]) % M + (A[i - 2] + P[i - 2]) % M) % M;
        if (i > 2) A[i] = ((A[i - 1] + A[i - 2]) % M + A[i - 3]) % M;
    }
    return ((A[n - 1] + P[n - 1]) % M + L[n - 1]) % M;
}

//dp[i][j]=dp[i-1][j]+dp[i][j-1]
class UniquePaths {
public:
    int uniquePaths(int m, int n) {
        if(m==0||n==0)
            return 0;
        //dp[i][j]=dp[i-1][j]+dp[i][j-1]
        vector<int> dp(n,1);
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[j]=dp[j]+dp[j-1];
            }
        }
        return dp[n-1];
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size(),n=obstacleGrid[0].size();
        vector<int> dp(n,0);
        for(int i=0;i<n;i++){
            if(obstacleGrid[0][i]==1){
                dp[i]=0;
                break;
            }
            else dp[i]=1;
        }
        int lowbound=INT_MAX;
        for(int i=0;i<m;i++){
            if(obstacleGrid[i][0]==1){
                lowbound=i;
                break;
            }
        }

        for(int i=1;i<m;i++){
            for(int j=0;j<n;j++){
                if(j==0){
                    if(i>=lowbound)
                        dp[j]=0;
                }
                if(!obstacleGrid[i][j])
                    dp[j]+=dp[j-1];
                else dp[j]=0;
            }
        }
        return dp.back();
    }
};

//dp[i]=OR(dp[j]&&j+nums[j]>=i )for all j<i
class JumpGame {
public:
    bool canJump(vector<int>& nums) {
        int n=nums.size();
        vector<bool> dp(n,false);
        dp[0]=true;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(dp[j]&&j+nums[j]>=i){
                    dp[i]=true;
                    break;
                }
            }
        }
        return dp.back();
    }
};