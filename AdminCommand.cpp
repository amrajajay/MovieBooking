#include "BookTicket.h"
#include "AdminCommand.h"
#include "BookingQueue.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void AdminCommand::get_booking_info()
{
    vector<BookTicket> tickets = get_all_bookings();
    BookingQueue q;
    BookTicket t;
    t.tostring(true);
    for (BookTicket ticket : tickets)
    {
        q.enQueue(ticket);
    }
    try
    {
        q.view();
        while (true)
        {
            q.deQueue();
        }
    }
    catch (const BookingQueue::QueueEmptyException &e)
    {
        cout << e.what() << endl;
    }
    return;
}