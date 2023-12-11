#include "BinaryNode.h"
using namespace std;
BinaryNode::BinaryNode()
{
    left = right = nullptr;
}
BinaryNode::BinaryNode(BookTicket data)
{
    this->data = data;
    left = right = nullptr;
}