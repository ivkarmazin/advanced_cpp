#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "set.h"
using namespace std;

int main() {
    srand(time(NULL));

    TreapNode<int>* root = NULL;
    root = root->insert(root, 50);
    root = root->insert(root, 30);
    root = root->insert(root, 20);
    root = root->insert(root, 40);
    root = root->insert(root, 70);
    root = root->insert(root, 60);
    root = root->insert(root, 80);
    root = root->insert(root, 80);

    cout << root->minKey(root)->key << endl;
   
    cout << "Inorder traversal of the given tree \n";
    root->inorder(root);
 
    cout << "\nDelete 20\n";
    root = root->deleteNode(root, 20);
    cout << "Inorder traversal of the modified tree \n";
    root->inorder(root);
 
    cout << "\nDelete 30\n";
    root = root->deleteNode(root, 30);
    cout << "Inorder traversal of the modified tree \n";
    root->inorder(root);
 
    cout << "\nDelete 50\n";
    root = root->deleteNode(root, 50);
    cout << "Inorder traversal of the modified tree \n";
    root->inorder(root);

    cout << "\nDelete 50\n";
    root = root->deleteNode(root, 50);
    cout << "Inorder traversal of the modified tree \n";
    root->inorder(root);

    TreapNode<int> *res = root->find(root, 50);
    (res == NULL)? cout << "\n50 Not Found " << endl:
                   cout << "\n50 found << endl";

    cout << "lb 55: " << root->lower_bound(root, 55)->key << endl;
    cout << "lb 60: " << root->lower_bound(root, 60)->key << endl;

    cout << endl;
    Set<int> bst0 { 6, 9, 3, 12, 5, 69, 2, 55, 4 };

    int elems[] = {3, 3, -1, 6, 0, 0, 17, -5, 4, 2};
    Set<int> bst(elems, elems + 10);
    bst.insert(1);
    bst.erase(17);

    using BstIter = Set<int>::iterator;

    BstIter it = bst.begin();
    BstIter it_end = bst.end();

    std::cout << "it == it: " << (it == it) << "\n";
    std::cout << "it != it: " << (it != it) << "\n";

    std::cout << "First value: " << *it << "\n";
    std::cout << "Second value: " << *(++it) << "\n";
    std::cout << "Previous value: " << *(--it) << "\n";

    cout << "bst0, initializer_list\n";
    for (const auto& n : bst0)
        std::cout << n << " ";

    cout << endl;
    cout << "bst, two iterators:\n"; 
    std::for_each(bst.begin(), bst.end(),
        [](const auto& n) { std::cout << n << " "; });

    cout << endl << "bst empty: " << bst.empty() << " bst.size: " << bst.size() << endl;

    return 0;
}

// sources:
//geeksforgeeks.org
//stackoverflow.com
//anderberg.me/2016/07/04/c-custom-iterators/
