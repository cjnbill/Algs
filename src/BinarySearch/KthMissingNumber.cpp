//
// Created by cjn on 2018/5/18.
//

#include <vector>
using namespace std;

static int countingSort(vector<int> arr, int k, int s, int e) {
    int mid = s + ((e - s) / 2);
    if (mid == s) {
        return arr[mid] + 1;
    }
    int i1 =   arr[mid]-((mid - s) + arr[s]);
    if (i1 >= (k + 1)) {
        return countingSort(arr, k, s, mid);
    } else {
        return countingSort(arr, k - i1, mid, e);
    }
}
