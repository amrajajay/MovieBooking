#ifndef BOOKINGNODE_H
#define BOOKINGNODE_H
#include "BookTicket.h"
struct BookingNode{
    BookTicket data;
    BookingNode* next;
    BookingNode* prev;
    BookingNode(BookTicket);
};
#endif  