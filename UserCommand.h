#ifndef USERCOMMAND_H
#define USERCOMMAND_H
#include <iostream>
#include "Command.h"
#include "BookTicket.h"
#include <vector>
using namespace std;
class UserCommand : public Command
{
public:
    void get_booking_info() override;
};
#endif