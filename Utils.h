
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <vector>
#include "Movie.h"
#include "BookTicket.h"
class Movie;
using namespace std;
class Utils
{
public:
    static const string show_slots[4];
    static vector<Movie> readMovieData(string);
    static void display_movies_using_stack();
    static void add_movie_to_db();
    static void write_movie_to_file(vector<Movie>, string, bool);
    static vector<Movie> readBookingData(string);
    static bool isDateInRange(tm start, tm end);
    static void book_ticket();
    static tm getCurrentDate();
    static tm getTomorrowDate();
    static tm getDayAfterTomorrowDate();
    static void printDate(tm);
    static int view_all_bookings_in_queue();
    static vector<BookTicket> get_all_bookings();
    static void get_booking_info(bool);
    static void cancel_booking(string bookingID);
    static void remove_movie_from_db(int);
    static void update_movie_in_db(int);
    static void get_min_life_span_movie();
};

#endif
