#pragma once
#include "treap.h"

using namespace std;

template <typename T>
TreapNode<T>::TreapNode(const T&  key, const int& priority): 
    key(key), priority(priority), size(1), left(NULL), right(NULL), parent(NULL)
{}

template <typename T>
TreapNode<T>* TreapNode<T>::newNode(T key) 
{
    TreapNode<T>* temp = new TreapNode<T>;
    temp->key = key;
    temp->priority = rand() % 900 + 100;
    temp->size = 1;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

template <typename T>
int TreapNode<T>::getSize(TreapNode<T>* node)
{
    if(node == NULL)
        return 0;
    else
        return node->size;
}

template <typename T>
void TreapNode<T>::mend(TreapNode<T>* node)
{
    node->size = node->getSize(node->left) + node->getSize(node->right) + 1;
}

template <typename T>
TreapNode<T>* TreapNode<T>::rightRotate(TreapNode<T> *y)
{
    TreapNode<T> *x = y->left,  *T2 = x->right;
    x->right = y;
    x->parent = y->parent;
    y->left = T2;
    y->parent = x;
    if (T2 != NULL) 
        T2->parent = y;
    x->mend(x);
    y->mend(y);
    return x;
}

template <typename T>
TreapNode<T>* TreapNode<T>::leftRotate(TreapNode<T> *x)
{
    TreapNode<T> *y = x->right, *T2 = y->left;
    y->left = x;
    y->parent = x->parent;
    x->right = T2;
    x->parent = y;
    if (T2 != NULL) 
        T2->parent = x;
    x->mend(x);
    y->mend(y);
    return y;
}

template <typename T>
TreapNode<T>* TreapNode<T>::minKey(TreapNode<T>* node)
{
    const TreapNode<T>* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return const_cast<TreapNode<T>*>(current);
    //return current;
}

template <typename T>
TreapNode<T>* TreapNode<T>::maxKey(TreapNode<T>* node)
{
    TreapNode<T>* current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

template <typename T>
TreapNode<T>* TreapNode<T>::insert(TreapNode<T>* root, const T& key)
{
    if (!root)
        return newNode(key);
 
    if (key < root->key)
    {
        //root->left = insert(root->left, key);
        TreapNode<T>* lchild = insert(root->left, key);
        root->left  = lchild;
        lchild->parent = root;
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else if ( (!( (!(key < root->key)) && (!(root->key < key)) )) && !(key < root->key) )
    {
        //root->right = insert(root->right, key);
        TreapNode<T>* rchild = insert(root->right, key);
        root->right  = rchild;
        rchild->parent = root;
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    root->mend(root);
    return root;
}

template <typename T>
TreapNode<T>*  TreapNode<T>::deleteNode(TreapNode<T>* root, const T& key)
{
    if (root == NULL)
        return root;
 
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (root->key < key)
        root->right = deleteNode(root->right, key);
 
    else if (root->left == NULL)
    {
        TreapNode<T> *temp = root->right;
        if (temp != NULL)
            temp->parent = root->parent;
        delete(root);
        root = temp; 
    }
 
    else if (root->right == NULL)
    {
        TreapNode<T> *temp = root->left;
        if (temp != NULL)
            temp->parent = root->parent;
        delete(root);
        root = temp;  
    }
    
    else if (root->left->priority < root->right->priority)
    {
        root = leftRotate(root);
        root->left = deleteNode(root->left, key);
    }
    else
    {
        root = rightRotate(root);
        root->right = deleteNode(root->right, key);
    }
    if (root != NULL)
        root->mend(root);
    return root;
}

template <typename T>
TreapNode<T>* TreapNode<T>::find(TreapNode<T>* root, const T& key)
{
    if (root == NULL || ((!(root->key < key)) && (!(key < root->key))))
       return root;
 
    if (root->key < key)
       return find(root->right, key);
 
    return find(root->left, key);
}

template <typename T>
TreapNode<T>* TreapNode<T>::lower_bound(TreapNode* root, const T& key)
{ 
    bool maximum = true;
    if (root == NULL)
        return NULL;
    while (true){
        if (key < root->key){
            if (root->left == NULL)
                return root;
            else root = root->left;
            maximum = false;
        }
        else {
            if (root->right == NULL)
                if (!maximum){
                    TreapNode<T>* p = root->parent;
                    while (p != NULL && root == p->right) {
                        root = p;
                        p = p->parent;
                    }
                    return p;
                }
                else 
                    return NULL;
            root = root->right;
        }
    }
}

template <typename T>
TreapNode<T>* TreapNode<T>::successor(TreapNode<T>* node)
{
    if (node == NULL)
        return NULL;
    if (node->right != NULL)
        return minKey(node->right);
 
    TreapNode<T>* p = node->parent;
    while (p != NULL && node == p->right) {
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename T>
TreapNode<T>* TreapNode<T>::predecessor(TreapNode<T>* node)
{
    if (node == NULL)
        return NULL;
    if (node->left != NULL)
        return maxKey(node->left);
 
    TreapNode<T>* p = node->parent;
    while (p != NULL && node == p->left) {
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename T>
void TreapNode<T>::inorder(const TreapNode<T>* root) const
{
    if (root)
    {
        inorder(root->left);
        cout << "key: "<< root->key << " | pr: "
            << root->priority << " | sz: " << root->size;
        if (root->parent)
            cout << " | par: " << root->parent->key;
        else  
            cout << " | par: " << "  ";
        if (root->left)            
            cout << " | left: " << root->left->key;
        else  
            cout << " | left: " << "  ";
        if (root->right)
            cout << " | right: " << root->right->key;
        else  
            cout << " | right: " << "  ";
        cout << endl;
        inorder(root->right);
    }
}    

template <typename T>
bool TreapNode<T>::empty(const TreapNode<T>* root) const
{
    if (root == NULL)
        return true;
    else
        return false;
}

template <typename T>
bool TreapNode<T>::operator==(const TreapNode<T>* rhs)
{
    if(this == NULL || rhs == NULL){
        if(this == NULL && rhs == NULL)
            return true;
        else
            return false;
    }
    else{
        if(this->key == rhs->key)
            return true;
        else
            return false;
    }
}