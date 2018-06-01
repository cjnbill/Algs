//
// Created by cjn on 2018/5/24.
//
#include <vector>
#include <cstdlib>

using namespace std;
//蓄水池采样算法（Reservoir Sampling）
//对于第 i 个数（i≤k）。在 k 步之前，被选中的概率为 1。当走到第 k+1 步时，被 k+1 个元素替换的概率 = k+1 个元素被选中的概率 * i 被选中替换的概率，即为 kk+1×1k=1k+1。则被保留的概率为 1−1k+1=kk+1。依次类推，不被 k+2 个元素替换的概率为 1−kk+2×1k=k+1k+2。则运行到第 n 步时，被保留的概率 = 被选中的概率 * 不被替换的概率，即：
//
//1×kk+1×k+1k+2×k+2k+3×…×n−1n=kn
//
//对于第 j 个数（j>k）。在第 j 步被选中的概率为 kj。不被 j+1 个元素替换的概率为 1−kj+1×1k=jj+1。则运行到第 n 步时，被保留的概率 = 被选中的概率 * 不被替换的概率，即：
//
//kj×jj+1×j+1j+2×j+2j+3×...×n−1n=kn
//
//所以对于其中每个元素，被保留的概率都为 k/n.

static vector<int> sampling(int K,vector<int>& pool) {
    vector<int> result(K);
    for (int i = 0; i < K; i++) { // 前 K 个元素直接放入数组中
        result[i] = pool[i];
    }

    srand(time(0));
    for (int i = K; i < pool.size(); i++) { // K + 1 个元素开始进行概率采样
        int r = rand()%(i+1);
        if (r < K) {
            result[r] = pool[i];
        }
    }

    return result;
}

static vector<vector<int>> gen_table(int n){
    if(n<0)
        return {};
    vector<vector<int>> table(n,vector<int>(n,-1));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            auto color=rand()%3;
            if(i<2&&j<2) {
                table[i][j] = color;
                continue;
            }

            bool flag =  false;
            while(!flag){
                if((j>=2&&(table[i][j-1]==color&&table[i][j-2]==color))
                   ||(i>=2&&(table[i-1][j]==color&&table[i-2][j]==color)))
                    color=rand()%3;
                else flag=true;
            }
            table[i][j]=color;
        }
    }
    return table;
}
//shuffle(v.begin(),v.end());
vector<int> shuffle(vector<int>& v) {
    int n=v.size();
    srand(time(0));
    for (int i = n; i != 0; i--) {
        int j = rand()%(i+1);
        swap(v[i],v[j]);
    }
    return v;
}