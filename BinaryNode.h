#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <iostream>
#include "BookTicket.h"
using namespace std;

class BinaryNode
{
public:
    BookTicket data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode();
    BinaryNode(BookTicket);
};
#endif
