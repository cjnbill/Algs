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


class BuyAndSellStock {
public:
    //121. Best Time to Buy and Sell Stock with one transaction
    int maxProfit1(vector<int>& prices) {
        int min_price=INT_MAX, max_profit=0;
        for(auto price:prices){
            int cur_profit=price-min_price;
            max_profit=max(max_profit,cur_profit);
            min_price=min(min_price,price);
        }
        return max_profit;
    }
    //122. Best Time to Buy and Sell Stock II
    //greedy
    int maxProfit2(vector<int> &prices) {
        int ret = 0;
        for (size_t p = 1; p < prices.size(); ++p)
            ret += max(prices[p] - prices[p - 1], 0);
        return ret;
    }
    //188. Best Time to Buy and Sell Stock IV with k transaction
    //我们定义local[i][j]为在到达第i天时最多可进行j次交易并且最后一次交易在最后一天卖出的最大利润，此为局部最优。
    // 然后我们定义global[i][j]为在到达第i天时最多可进行j次交易的最大利润，此为全局最优。它们的递推式为：
    //local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff)
    //
    //global[i][j] = max(local[i][j], global[i - 1][j])
    int maxProfit3(vector<int> &prices,int k) {
        if (prices.empty()) return 0;
        int n = prices.size(), g[n][k+1] = {0}, l[n][k+1] = {0};
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i - 1];
            for (int j = 1; j <= 2; ++j) {
                l[i][j] = max(g[i - 1][j - 1] + max(diff, 0), l[i - 1][j] + diff);
                g[i][j] = max(l[i][j], g[i - 1][j]);
            }
        }
        return g[n - 1][k];
    }
    //with cool down
    //buy[i]  = max(rest[i-1] - price, buy[i-1])
    //sell[i] = max(buy[i-1] + price, sell[i-1])
    //rest[i] = max(sell[i-1], buy[i-1], rest[i-1])

    //optimize to:
    //buy[i]  = max(sell[i-2] - price, buy[i-1])
    //sell[i] = max(buy[i-1] + price, sell[i-1])
    int maxProfit4(vector<int>& prices) {
        int buy = INT_MIN, pre_buy = 0, sell = 0, pre_sell = 0;
        for (int price : prices) {
            pre_buy = buy;
            buy = max(pre_sell - price, pre_buy);
            pre_sell = sell;
            sell = max(pre_buy + price, pre_sell);
        }
        return sell;
    }
};

//Perfect Squares
class PerfectSquare {
public:
    /**
     * @param n a positive integer
     * @return an integer
     */
    int numSquares(int n) {
        // Write your code here
        vector<int> dp{ 0 };
        dp.resize(n + 1, INT_MAX);
        for(int i = 1; i * i <= n; ++i) {
            dp[i * i] = 1;
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }

        return dp[n];
    }
};

//21 points
//calculate prob of lose
static double lostProMM(int sum, double& mm[]) {
    if (sum >=17 && sum <= 21) return 0;
    if (sum > 21) return 1;
    if (mm[sum] != nullptr) return mm[sum];
    double T = 0;
    for (int i = 1; i <= 10; ++ i)
        T += lostProMM(sum + i, mm) * 0.1;
    return mm[sum] = T;
}

class _21Game {
public:
    //Alice plays the following game, loosely based on the card game "21".
    //Alice starts with 0 points, and draws numbers while she has less than K points.
    // During each draw, she gains an integer number of points randomly from the
    // range [1, W], where W is an integer.  Each draw is independent and the outcomes
    // have equal probabilities.
    //Alice stops drawing numbers when she gets K or more points.  What is the probability that she has N or less points?
    double new21Game(int N, int K, int W) {
        if (K == 0) {
            return 1;
        }
        int max = K + W - 1;
        double dp[max+1];
        dp[0] = 1;
        for (int i = 1; i <= max; i++) {
            for (int j = 1; j <= W; j++) {
                if (i - j >= 0 && i - j < K) {
                    dp[i] += dp[i - j] / W;
                }
            }
        }
        double result = 0;
        for (int i = K; i <= N; i++) {
            result += dp[i];
        }
        return result;
    }

    double New21Game(int N, int K, int W) {

        if(N >= K+W-1) return 1.0; // all possibilities of positions after alice stops playing are from [K, K+W-1]

        double p[K+W];
        double prob = 1/(W+0.0); // single elem probability

        double prev = 0;

        p[0] = 1; // Since we start from 0, initialize it to 1

        //Until K
        for(int i = 1; i <= K; i++) {
            prev = prev - (i-W-1 >= 0 ? p[i - W -1] : 0) + p[i-1];
            p[i] = prev*prob;
        }

        double req = p[K];

        // From K+1, we don't add the p[i-1] term here as it is >= K
        for(int i = K+1; i <= N; i++) {
            prev = prev - (i-W-1 >= 0 ? p[i - W -1] : 0);
            p[i] = prev * prob;
            req += p[i];
            //System.out.println(p[i]);
        }

        return req;
    }
};