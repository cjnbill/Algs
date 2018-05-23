//
// Created by cjn on 2018/5/18.
//

#include <vector>
#include <iostream>
using namespace std;

static int kthMissingHelper(vector<int>& arr, int low, int high, int k){
    if(low==high-1){
        int numRange = arr[high] - arr[low];
        int numPresent = high - low;
        int totalMissing = numRange - numPresent;
        if(k > totalMissing)
            return -1;
        return arr[low]+k;
    }
    int middle = (low + high)/2;
    int missingCountInLeft = (arr[middle] - arr[low]) - (middle - low);


    if(missingCountInLeft >= k)
        return kthMissingHelper(arr, low, middle, k);
    else
        return kthMissingHelper(arr, middle, high, k - (missingCountInLeft));
}

static int findKthMissing(vector<int>& arr, int k){
    return kthMissingHelper(arr, 0, arr.size()-1, k);
}


