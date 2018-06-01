//
// Created by cjn on 2018/5/24.
//
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Function to sort arr[] of size n using bucket sort
void bucketSort(float arr[], int n)
{
    // 1) Create n empty buckets
    vector<float> b[n];

    // 2) Put array elements in different buckets
    for (int i=0; i<n; i++)
    {
        int bi = n*arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i=0; i<n; i++)
        sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

//For simplicity, consider the data in the range 0 to 9.
//Input data: 1, 4, 1, 2, 7, 5, 2
//  1) Take a count array to store the count of each unique object.
//  Index:     0  1  2  3  4  5  6  7  8  9
//  Count:     0  2  2  0   1  1  0  1  0  0
//
//  2) Modify the count array such that each element at each index
//  stores the sum of previous counts.
//  Index:     0  1  2  3  4  5  6  7  8  9
//  Count:     0  2  4  4  5  6  6  7  7  7
//
//The modified count array indicates the position of each object in
//the output sequence.
//
//  3) Output each object from the input sequence followed by
//  decreasing its count by 1.
//  Process the input data: 1, 4, 1, 2, 7, 5, 2. Position of 1 is 2.
//  Put data 1 at index 2 in output. Decrease count by 1 to place
//  next data 1 at an index 1 smaller than this index.

void countSort(char arr[],int RANGE)
{
    // The output character array that will have sorted arr
    char output[strlen(arr)];

    // Create a count array to store count of inidividul
    // characters and initialize count array as 0
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));

    // Store count of each character
    for(i = 0; arr[i]; ++i)
        ++count[arr[i]];

    // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i-1];

    // Build the output character array
    for (i = 0; arr[i]; ++i)
    {
        output[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }

    // Copy the output array to arr, so that arr now
    // contains sorted characters
    for (i = 0; arr[i]; ++i)
        arr[i] = output[i];
}