#include <iostream>
using namespace std;

#include "MedianFinder.cc"

int main()
{
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout<<mf.findMedian()<<endl;
    mf.addNum(3);
    cout<<mf.findMedian()<<endl;
}