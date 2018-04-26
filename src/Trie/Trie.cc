//
// Created by cjn on 2018/4/6.
//

#include "Trie.h"

TrieNode::TrieNode():child_(26, nullptr),is_word_(false){}

Trie::Trie() {
    root_ = new TrieNode();
}

/** Inserts a word into the trie. */
void Trie::Insert(string &word) {
    auto cur=root_;
    for(auto &c : word) {
        int i=c-'a';
        if(!cur->child_[i])cur->child_[i] = new TrieNode();
        cur=cur->child_[i];
    }
    cur->is_word_=true;
}

/** Returns if the word is in the trie. */
bool Trie::Search(string &word) {
    auto node = SearchWordNode(word);
    if(!node)
        return false;
    return node->is_word_;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool Trie::StartWith(string &prefix) {
    auto node= SearchWordNode(prefix);
    return node!=nullptr;
}
/** Returns word end where in the trie. */
TrieNode* Trie::SearchWordNode(string &word){
    auto cur = root_;
    for (auto &c : word) {
        int i = c - 'a';
        if(!cur->child_[i])return nullptr;
        cur = cur -> child_[i];
    }
    return cur;
}