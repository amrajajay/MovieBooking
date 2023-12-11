#ifndef ADMINCOMMAND_H
#define ADMINCOMMAND_H
#include <iostream>
#include "Command.h"
#include "BookTicket.h"
#include <vector>
using namespace std;
class AdminCommand : public Command
{
public:
    virtual void get_booking_info();
    // vector<BookTicket> get_all_bookings();
};
#endif