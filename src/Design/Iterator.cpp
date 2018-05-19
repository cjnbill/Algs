//
// Created by cjn on 2018/5/16.
//

#include <stack>
#include <vector>
using namespace std;

class NestedInteger {
    public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;
    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i=nestedList.size()-1;i>=0;i--){
            s1.push(nestedList[i]);
        }
    }

    int next() {
        if(hasNext()){
            int res=s1.top().getInteger();s1.pop();
            return res;
        }
        return -1;
    }

    bool hasNext() {
        while(!s1.empty()&&!s1.top().isInteger()){
            auto l=s1.top().getList();
            s1.pop();
            for(int i=l.size()-1;i>=0;i--){
                s1.push(l[i]);
            }
        }
        return !s1.empty();
    }
private:
    stack<NestedInteger> s1;
};

//flatten 2d vector
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d){
        for(int i=vec2d.size()-1;i>=0;i--){
            s1.push(vec2d[i]);
        }
    }

    int next() {
        int res=0;
        if(hasNext()){
            res=s2.top();s2.pop();
        }
        return res;
    }

    bool hasNext() {
        if(s2.empty()){
            while(!s1.empty()&&s2.empty()){
                auto v=s1.top();s1.pop();
                for(int i=v.size()-1;i>=0;i--){
                    s2.push(v[i]);
                }
            }
        }
        return !s2.empty();
    }
private:
    stack<vector<int>> s1;
    stack<int> s2;
};


//BST Iterator

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        p=root;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        while(p){
            s.push(p);
            p=p->left;
        }
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        if(!hasNext()){
            return -1;
        }
        auto t=s.top();s.pop();
        p=t->right;
        return t->val;
    }
private:
    stack<TreeNode*> s;
    TreeNode* p;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

