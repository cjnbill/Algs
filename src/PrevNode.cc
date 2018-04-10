//
// Created by cjn on 2018/4/5.
//
#include <iostream>
struct Node{
    int val;
    Node* parent;
    Node* first_sibling;
    Node* next_sibling;
    Node* first_child;
    Node* last_child;
};

Node* find_prev_node(Node* input){
    if(input->first_sibling==input){
        return input->parent;
    }
    else{
        Node *cur=input->first_sibling;
        while(cur&&cur->next_sibling!=input){
            cur=cur->next_sibling;
        }
        while(cur&&cur->last_child!= nullptr){
            cur=cur->last_child;
        }
        return cur;
    }
}
Node* test_find_prev_node(){
    Node *n1=new Node(),*n2=new Node(),*n3=new Node();
    n1->val=1,n2->val=2,n3->val=3;
    n1->first_child=n2;
    n1->last_child=n3;
    n2->next_sibling=n3;
    n2->parent=n1;
    n2->first_sibling=n2;
    n3->first_sibling=n2;
    n3->parent=n1;
    auto res=find_prev_node(n2);
    std::cout<<res->val;
    return 0;
}