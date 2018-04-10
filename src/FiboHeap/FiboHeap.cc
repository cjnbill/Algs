#include <iostream>
#include <cmath>
using namespace std;


template <class T>
class FiboNode {
    public:
        T key_;
        int degree_;
        bool childcut_;
        FiboNode<T> *left;
        FiboNode<T> *right;
        FiboNode<T> *child;
        FiboNode<T> *parent;

        FiboNode(T value):key_(value), degree_(0), childcut_(false),
            left(NULL),right(NULL),child(NULL),parent(NULL)
        {
            key_    = value;
            degree_ = 0;
            childcut_ = false;
            left   = this;
            right  = this;
            parent = NULL;
            child  = NULL;
        }
};

template <class T>
class FiboHeap {
    private:
        int keyNum;
        int maxDegree;
        FiboNode<T> *max;
        FiboNode<T> **cons;

    public:
        FiboHeap();
        ~FiboHeap();

        void insert(FiboNode<T> *node);
        void removeMax();
        void combine(FiboHeap<T> *other);
        void increaseKeyKey(FiboNode<T> *node, T key);
        void addNode(FiboNode<T> *node, FiboNode<T> *root);
        void removeNode(FiboNode<T> *node);
        FiboNode<T>* getMax();
        FiboNode<T>* extractMax();
        void print();
        void link(FiboNode<T>* node, FiboNode<T>* root);
        void makeCons();
        void consolidate();
        void renewDegree(FiboNode<T> *parent, int degree);
        void cut(FiboNode<T> *node, FiboNode<T> *parent);
        void cascadingCut(FiboNode<T> *node) ;
        void increaseKey(FiboNode<T>* node, T key);

};

template <class T>
FiboHeap<T>::FiboHeap()
{
    keyNum = 0;
    maxDegree = 0;
    max = NULL;
    cons = NULL;
}

template <class T>
FiboHeap<T>::~FiboHeap()
{
}

//add node to the left of root
template <class T>
void FiboHeap<T>::addNode(FiboNode<T> *node, FiboNode<T> *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

//insert node to the heap
template <class T>
void FiboHeap<T>::insert(FiboNode<T> *node)
{
    if(keyNum==0)
        max=node;
    else{
        addNode(node,max);
        if(max->key_<node->key_)
            max=node;
    }
    keyNum++;
}

//remove from the sibling linked-list
template <class T>
void FiboHeap<T>::removeNode(FiboNode<T> *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

//get max pointer
template <class T>
FiboNode<T>* FiboHeap<T>::getMax()
{
    return max;
}

//get the max node with it's subtree
template <class T>
FiboNode<T>* FiboHeap<T>::extractMax()
{
    FiboNode<T> *p = max;

    if (p == p->right)
        max = NULL;
    else
    {
        removeNode(p);
        max = p->right;
    }
    p->left = p->right = p;

    return p;
}

//combine to  tree,set one tree as the child of the other
template <class T>
void FiboHeap<T>::link(FiboNode<T>* node, FiboNode<T>* root)
{
    removeNode(node);
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree_++;
    node->childcut_ = false;
}

//make memory for consolidate
template <class T>
void FiboHeap<T>::makeCons()
{
    int old = maxDegree;

    // calculate the max degree =log2(keyNum)
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;

    cons = (FiboNode<T> **)realloc(cons,
            sizeof(FiboHeap<T> *) * (maxDegree + 1));
}

//combine the same dgreee tree in the root link list
template <class T>
void FiboHeap<T>::consolidate()
{
    int i, d, D;
    FiboNode<T> *x, *y, *tmp;

    makeCons();
    D = maxDegree + 1;

    for (i = 0; i < D; i++)
        cons[i] = NULL;

    while (max != NULL)
    {
        x = extractMax();
        d = (x->degree_);
        // cons[d] != NULL，means there are two trees have same degree
        while (cons[d] != NULL)
        {
            y = cons[d];                // y has same degree with x
            if (x->key_ < y->key_)        // make sure x>y
                swap(*x, *y);

            link(y, x);    // combine x and y
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    max = NULL;

    // add nodes in the cons back to heap
    for (i=0; i<D; i++)
    {
        if (cons[i] != NULL)
        {
            if (max == NULL)
                max = cons[i];
            else
            {
                addNode(cons[i], max);
                if ((cons[i])->key_ > max->key_)
                    max = cons[i];
            }
        }
    }
}



template <class T>
void FiboHeap<T>::removeMax()
{
    if (max==NULL)
        return ;

    FiboNode<T> *child = NULL;
    FiboNode<T> *m = max;
    // move every child of max to the root link list
    while (m->child != NULL)
    {
        child = m->child;
        removeNode(child);
        if (child->right == child)
            m->child = NULL;
        else
            m->child = child->right;

        addNode(child, max);
        child->parent = NULL;
    }

    removeNode(m);
    if (m->right == m)
        max = NULL;
    else
    {
        max = m->right;
        consolidate();
    }
    keyNum--;

    delete m;
}

//change the node's degree
template <class T>
void FiboHeap<T>::renewDegree(FiboNode<T> *node, int degree)
{
    node->degree_ -= degree;
}


//cut node off the parent and move it to the root link list
template <class T>
void FiboHeap<T>::cut(FiboNode<T> *node, FiboNode<T> *parent)
{
    removeNode(node);
    //renewDegree(parent, node->degree);
    renewDegree(parent, parent->degree_-1);

    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->childcut_ = false;
    addNode(node, max);
}


//do the cascadingCut
template <class T>
void FiboHeap<T>::cascadingCut(FiboNode<T> *node)
{
    FiboNode<T> *parent = node->parent;
    if (parent != NULL)
    {
        if (!node->childcut_)
            node->childcut_ = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

template <class T>
void FiboHeap<T>::increaseKey(FiboNode<T> * node, T key)
{
    FiboNode<T> *parent;

    if (max==NULL ||node==NULL)
        return ;

    if ( key<=node->key_)
    {
        cout << "decrease failed: the new key(" << key <<") "
             << "is no larger than current key(" << node->key_ <<")" << endl;
        return ;
    }

    node->key_ = key;
    parent = node->parent;
    if (parent!=NULL && node->key_ > parent->key_)
    {
        cut(node, parent);
        cascadingCut(parent);
    }

    if (node->key_ > max->key_)
        max = node;
}


