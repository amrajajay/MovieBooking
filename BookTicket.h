#ifndef BOOKTICKET_H
#define BOOKTICKET_H
#include <iostream>
using namespace std;
class BookTicket
{

    string booking_id;
    int movie_id;
    tm booking_date;
    string time_slot;
    int no_of_seats;
    // string seats_reserved;
    string generateBookingID();
    // tm* booked_date;

public:
    BookTicket(int, tm, string, int);
    BookTicket();
    void validate_and_book_ticket();
    int get_movie_id();
    string get_time_slot();
    int get_no_of_seats();
    string get_booking_id();
    tm get_booking_date();
    tm get_booked_date();

    void set_movie_id(int);
    void set_time_slot(string);
    void set_no_of_seats(int);
    void set_booking_id(string);
    void set_booking_date(tm);
    int get_free_seats();
    void write_to_file();
    bool operator==(const string &) const;

    string tostring(bool);

    const static string BOOKINGS_FILE;
    static tm get_date_from_string(string);
    static bool areTmDatesEqual(tm &date1, const tm &date2);
};
#endif