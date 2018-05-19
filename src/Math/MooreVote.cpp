//
// Created by cjn on 2018/5/5.
//
#include <vector>
using namespace std;

//每次删除三个不相同的数，最后出现次数超过1/3的数会留下来，然后在验证是否真的大于1/3，这个思想可以推广到出现次数超过1/k次的元素有哪些
class MooreVote {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        int m = 0, n = 0, cm = 0, cn = 0;
        for (auto &a : nums) {
            if (a == m) ++cm;
            else if (a ==n) ++cn;
            else if (cm == 0) m = a, cm = 1;
            else if (cn == 0) n = a, cn = 1;
            //delete (m,n,a)
            else --cm, --cn;
        }
        cm = cn = 0;
        for (auto &a : nums) {
            if (a == m) ++cm;
            else if (a == n) ++cn;
        }
        if (cm > nums.size() / 3) res.push_back(m);
        if (cn > nums.size() / 3) res.push_back(n);
        return res;
    }
};