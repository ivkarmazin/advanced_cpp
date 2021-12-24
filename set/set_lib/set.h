#pragma once
#include "treap.h"
#include "list"
#include <iterator>

using namespace std;

template <typename T>
class BstIterator;

template <typename T>
class Set {
public:
    Set() = default;
    explicit Set(std::initializer_list<T> il);
    template <typename Iterator> 
    Set(Iterator first, Iterator last);
    ~Set() {recursiveDelete(root);}

    Set(const Set&);
    Set(Set&&) = delete;
    Set& operator=(const Set&);
    Set& operator=(Set&&) = delete;

    void insert(const T& value);
    void erase(const T& value);
    int size() const;
    bool empty() const;

    using iterator = BstIterator<T>;
    using const_iterator = BstIterator<const T>;
    iterator begin() const;
    iterator end() const;
    iterator find(const T& value) const;
    iterator lower_bound(const T& value) const;

    TreapNode<T>* root{NULL};
private:
    bool iteratorValid;
    TreapNode<T>* copy(TreapNode<T>* p);
    void recursiveDelete(TreapNode<T>* root);
};



template <typename T>
class BstIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;

    BstIterator() = default;
    BstIterator(Set<T> const* my_setPtr, TreapNode<T>* node);

    reference operator*() const;
    pointer operator->() const { return &(operator*()); }

    BstIterator& operator++();
    BstIterator operator++(int);
    BstIterator& operator--();
    BstIterator operator--(int);

    bool operator==(const BstIterator& rhs);
    bool operator!=(const BstIterator& rhs);

private:
    Set<T> const* setPtr;
    TreapNode<T>* current;
};



#include "set.hpp"