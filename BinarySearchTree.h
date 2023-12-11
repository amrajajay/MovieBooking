#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H
#include <iostream>
#include <vector>
#include "BinaryNode.h"
// #include "BookTicket.h"
class BinarySearchTree
{
public:
    void insert(BookTicket &);
    void remove(BookTicket &);
    BookTicket search(string);

private:
    BinaryNode *root;
    bool search_and_insert(BinaryNode *&, BookTicket &);
    bool search_and_remove(BinaryNode *&, BookTicket &);
    BinaryNode *&get_successor(BinaryNode *&);
    BinaryNode *&search_in_bst(BinaryNode *&, string);
};

#endif