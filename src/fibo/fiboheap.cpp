#include <iostream>
#include <cmath>
using namespace std;


template <class T>
class fibonode {
    public:
        T key;
        int degree;
        bool childcut;
        fibonode<T> *left;
        fibonode<T> *right;
        fibonode<T> *child;
        fibonode<T> *parent;

        fibonode(T value):key(value), degree(0), childcut(false),
            left(NULL),right(NULL),child(NULL),parent(NULL)
        {
            key    = value;
            degree = 0;
            childcut = false;
            left   = this;
            right  = this;
            parent = NULL;
            child  = NULL;
        }
};

template <class T>
class fiboheap {
    private:
        int keyNum;
        int maxDegree;
        fibonode<T> *max;
        fibonode<T> **cons;

    public:
        fiboheap();
        ~fiboheap();

        void insert(fibonode<T> *node);
        void removeMax();
        void combine(fiboheap<T> *other);
        void increaseKeyKey(fibonode<T> *node, T key);
        void addNode(fibonode<T> *node, fibonode<T> *root);
        void removeNode(fibonode<T> *node);
        fibonode<T>* getMax();
        fibonode<T>* extractMax();
        void print();
        void link(fibonode<T>* node, fibonode<T>* root);
        void makeCons();
        void consolidate();
        void renewDegree(fibonode<T> *parent, int degree);
        void cut(fibonode<T> *node, fibonode<T> *parent);
        void cascadingCut(fibonode<T> *node) ;
        void increaseKey(fibonode<T>* node, T key);

};

template <class T>
fiboheap<T>::fiboheap()
{
    keyNum = 0;
    maxDegree = 0;
    max = NULL;
    cons = NULL;
}

template <class T>
fiboheap<T>::~fiboheap()
{
}

//add node to the left of root
template <class T>
void fiboheap<T>::addNode(fibonode<T> *node, fibonode<T> *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

//insert node to the heap
template <class T>
void fiboheap<T>::insert(fibonode<T> *node)
{
    if(keyNum==0)
        max=node;
    else{
        addNode(node,max);
        if(max->key<node->key)
            max=node;
    }
    keyNum++;
}

//remove from the sibling linked-list
template <class T>
void fiboheap<T>::removeNode(fibonode<T> *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

//get max pointer
template <class T>
fibonode<T>* fiboheap<T>::getMax()
{
    return max;
}

//get the max node with it's subtree
template <class T>
fibonode<T>* fiboheap<T>::extractMax()
{
    fibonode<T> *p = max;

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
void fiboheap<T>::link(fibonode<T>* node, fibonode<T>* root)
{
    removeNode(node);
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->childcut = false;
}

//make memory for consolidate
template <class T>
void fiboheap<T>::makeCons()
{
    int old = maxDegree;

    // calculate the max degree =log2(keyNum)
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;

    cons = (fibonode<T> **)realloc(cons,
            sizeof(fiboheap<T> *) * (maxDegree + 1));
}

//combine the same dgreee tree in the root link list
template <class T>
void fiboheap<T>::consolidate()
{
    int i, d, D;
    fibonode<T> *x, *y, *tmp;

    makeCons();
    D = maxDegree + 1;

    for (i = 0; i < D; i++)
        cons[i] = NULL;

    while (max != NULL)
    {
        x = extractMax();
        d = (x->degree);
        // cons[d] != NULL，means there are two trees have same degree
        while (cons[d] != NULL)
        {
            y = cons[d];                // y has same degree with x
            if (x->key < y->key)        // make sure x>y
                swap(x, y);

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
                if ((cons[i])->key > max->key)
                    max = cons[i];
            }
        }
    }
}



template <class T>
void fiboheap<T>::removeMax()
{
    if (max==NULL)
        return ;

    fibonode<T> *child = NULL;
    fibonode<T> *m = max;
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
void fiboheap<T>::renewDegree(fibonode<T> *node, int degree)
{
    node->degree -= degree;
}


//cut node off the parent and move it to the root link list
template <class T>
void fiboheap<T>::cut(fibonode<T> *node, fibonode<T> *parent)
{
    removeNode(node);
    //renewDegree(parent, node->degree);
    renewDegree(parent, parent->degree-1);

    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->childcut = false;
    addNode(node, max);
}


//do the cascadingCut
template <class T>
void fiboheap<T>::cascadingCut(fibonode<T> *node)
{
    fibonode<T> *parent = node->parent;
    if (parent != NULL)
    {
        if (!node->childcut)
            node->childcut = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

template <class T>
void fiboheap<T>::increaseKey(fibonode<T> * node, T key)
{
    fibonode<T> *parent;

    if (max==NULL ||node==NULL)
        return ;

    if ( key<=node->key)
    {
        cout << "decrease failed: the new key(" << key <<") "
             << "is no larger than current key(" << node->key <<")" << endl;
        return ;
    }

    node->key = key;
    parent = node->parent;
    if (parent!=NULL && node->key > parent->key)
    {
        cut(node, parent);
        cascadingCut(parent);
    }

    if (node->key > max->key)
        max = node;
}


