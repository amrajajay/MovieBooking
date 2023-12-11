
#include "Command.h"
#include "BookTicket.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
vector<BookTicket> Command::get_all_bookings()
{
    ifstream fin(BookTicket::BOOKINGS_FILE);
    vector<BookTicket> tickets;
    if (!fin.is_open())
    {
        cout << "unable to fetch Bookings" << endl;
    }
    else
    {

        string booking_data;
        getline(fin, booking_data);
        while (getline(fin, booking_data))
        {
            string bid, smid, slot, sseats, sbdate;
            istringstream iss(booking_data);
            iss >> bid >> smid >> sbdate >> slot >> sseats;
            BookTicket ticket;
            ticket.set_movie_id(stoi(smid));
            ticket.set_booking_id(bid);
            ticket.set_no_of_seats(stoi(sseats));
            ticket.set_time_slot(slot);
            ticket.set_booking_date(BookTicket::get_date_from_string(sbdate));
            tickets.push_back(ticket);
        }
    }
    fin.close();
    return tickets;
}