#include "UserCommand.h"
#include "BookTicket.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
using namespace std;

void UserCommand::get_booking_info()
{
    vector<BookTicket> bookings = get_all_bookings();
    cout << "Please enter booking id: ";
    string bookingId;
    cin >> bookingId;
    cout << endl;
    BinarySearchTree bst;
    for (BookTicket ticket : bookings)
    {
        // if (ticket == bookingId)
        // {
        //     cout << ticket.tostring(true);
        //     return;
        // }
        bst.insert(ticket);
    }
    // cout << "Ticket not found with given booking id" << endl;
    BookTicket res = bst.search(bookingId);
    if (res.get_booking_id() != bookingId)
    {
        cout << "Ticket not found with given booking id" << endl;
    }
    else
    {
        cout << res.tostring(true) << endl;
    }
}