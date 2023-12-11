#include "BookingNode.h"
#include "BookTicket.h"
#include <iostream>
using namespace std;
BookingNode::BookingNode(BookTicket data)
{
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
}