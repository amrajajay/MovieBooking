#include "BookTicket.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;
const string BookTicket::BOOKINGS_FILE = "bookings.txt";
BookTicket::BookTicket(int id, tm booking_date, string timslot, int no_of_seats)
{
    this->booking_id = "";
    this->movie_id = id;
    this->booking_date = booking_date;
    this->time_slot = timslot;
    this->no_of_seats = no_of_seats;
}
BookTicket::BookTicket() {}

int BookTicket::get_movie_id()
{
    return this->movie_id;
}
string BookTicket::get_time_slot()
{
    return this->time_slot;
}
int BookTicket::get_no_of_seats()
{
    return this->no_of_seats;
}
string BookTicket::get_booking_id()
{
    return this->booking_id;
}
tm BookTicket::get_booking_date()
{
    return this->booking_date;
}
void BookTicket::set_movie_id(int movie_id)
{
    this->movie_id = movie_id;
}
void BookTicket::set_time_slot(string time_slot)
{
    this->time_slot = time_slot;
}
void BookTicket::set_no_of_seats(int no_of_seats)
{
    this->no_of_seats = no_of_seats;
}
void BookTicket::set_booking_id(string booking_id)
{
    this->booking_id = booking_id;
}
void BookTicket::set_booking_date(tm booking_date)
{
    this->booking_date = booking_date;
}
void BookTicket::validate_and_book_ticket()
{
    this->booking_id = "";

    int avaliable_seats = get_free_seats();
    if (no_of_seats > avaliable_seats)
    {
        cout << "Requested tickets are greater than avalaiable tickets i.e " << avaliable_seats << endl;
    }
    else
    {
        this->booking_id = generateBookingID();
        this->write_to_file();
    }
}

int BookTicket::get_free_seats()
{
    int free_seats = 100;
    ifstream fin(BookTicket::BOOKINGS_FILE);
    if (!fin.is_open())
    {
        cout << "unable to fetch seats" << endl;
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
            tm bdate = get_date_from_string(sbdate);
            if (areTmDatesEqual(bdate, this->booking_date) && stoi(smid) == this->movie_id && slot == this->time_slot)
            {
                free_seats -= stoi(sseats);
            }
        }
        fin.close();
    }
    return free_seats;
}
tm BookTicket::get_date_from_string(string gdate)
{

    tm date = {};
    istringstream iss(gdate);
    char delimiter;
    iss >> date.tm_mon;  // Month (1-12)
    iss >> delimiter;    // Read and discard the '-'
    iss >> date.tm_mday; // Day of the month (1-31)
    iss >> delimiter;    // Read and discard the '-'
    iss >> date.tm_year; // Year (e.g., 2023)

    // Adjust the month and year to match tm structure conventions
    date.tm_mon -= 1;     // Adjust month (0-11)
    date.tm_year -= 1900; // Adjust year (years since 1900)

    return date;
}

bool BookTicket::areTmDatesEqual(tm &date1, const tm &date2)
{
    return (date1.tm_year == date2.tm_year &&
            date1.tm_mon == date2.tm_mon &&
            date1.tm_mday == date2.tm_mday);
}

string BookTicket::generateBookingID()
{
    int length = 10;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    string bookingID;
    srand(static_cast<unsigned>(time(nullptr))); // Initialize random seed

    for (int i = 0; i < length; ++i)
    {
        bookingID += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return bookingID;
}

string BookTicket::tostring(bool show_heading)
{
    stringstream ss;
    // tm booking_date= this->get_booking_date();
    string date_in_string = to_string(1 + booking_date.tm_mon) + "-" + to_string(booking_date.tm_mday) + "-" + to_string(1900 + booking_date.tm_year);
    // strftime(buffer, sizeof(buffer), "%Y-%m-%d", &booking_date);
    if (show_heading)
    {
        ss << left << setw(15) << "booking_id"
           << "  ";
        ss << left << setw(15) << "movie_id"
           << "  ";
        ss << left << setw(15) << "boking date"
           << "  ";
        ss << left << setw(15) << "time_slot"
           << "  ";
        ss << left << setw(15) << "no_of_seats" << endl;
    }
    ss << left << setw(15) << booking_id << "  ";
    ss << left << setw(15) << movie_id << "  ";
    ss << left << setw(15) << date_in_string << "  ";
    ss << left << setw(15) << time_slot << "  ";
    ss << left << setw(15) << no_of_seats << endl;

    return ss.str();
}
void BookTicket::write_to_file()
{
    bool flag = true;
    ifstream fin(BookTicket::BOOKINGS_FILE);
    if (fin)
    {
        string line;

        while (getline(fin, line))
        {
            flag = false;
            break;
        }
    }
    fin.close();

    ofstream fout(BookTicket::BOOKINGS_FILE, ios::app);
    if (!fout.is_open())
    {
        cout << "Server issue with theatre while confirming the tickets" << endl;
        this->booking_id = "";
        return;
    }
    cout << this->tostring(true);

    fout << this->tostring(flag);

    fout.close();
}

bool BookTicket::operator==(const string &rhs) const
{
    return this->booking_id == rhs;
}