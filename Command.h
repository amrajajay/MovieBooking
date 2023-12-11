#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include "BookTicket.h"
#include <vector>
using namespace std;

class Command
{
public:
   virtual void get_booking_info() = 0;
   vector<BookTicket> get_all_bookings();
};
#endif