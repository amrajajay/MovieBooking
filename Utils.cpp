#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <chrono>
#include <limits>
#include "Movie.h"
#include "Utils.h"
#include "MovieStack.h"
#include "BookTicket.h"
#include "BookingQueue.h"
#include "Command.h"
#include "AdminCommand.h"
#include "UserCommand.h"
#include "MinHeap.h"
using namespace std;

const string Utils::show_slots[4] = {"11AM", "2PM", "6PM", "9PM"};
vector<Movie> Utils::readMovieData(string filename)
{
    vector<Movie> movielist;
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "Unable to open file" << endl;
    }
    else
    {
        string movie_data;
        while (getline(fin, movie_data))
        {
            string id, name, a_f, a_t, rating;
            istringstream iss(movie_data);
            iss >> id >> name >> a_f >> a_t >> rating;
            Movie movie(stoi(id), name, BookTicket::get_date_from_string(a_f), BookTicket::get_date_from_string(a_t), rating);
            movielist.push_back(movie);
        }
        fin.close();
    }
    return movielist;
}

vector<Movie> Utils::readBookingData(string filename)
{
    vector<Movie> movielist;
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "Unable to open file" << endl;
    }
    else
    {
        string movie_data;
        while (getline(fin, movie_data))
        {
            string id, name, a_f, a_t, rating;
            istringstream iss(movie_data);
            iss >> id >> name >> a_f >> a_t >> rating;
            Movie movie(stoi(id), name, BookTicket::get_date_from_string(a_f), BookTicket::get_date_from_string(a_t), rating);
            movielist.push_back(movie);
        }
        fin.close();
    }
    return movielist;
}

void Utils::write_movie_to_file(vector<Movie> movielist, string filename, bool reset_file_if_exist)
{
    if (movielist.size() == 0)
        return;

    ofstream fout;
    if (reset_file_if_exist)
    {
        fout.open(filename);
    }
    else
    {
        fout.open(filename, ios::app);
    }
    if (!fout.is_open())
    {
        cout << "Unable to create movie DB please restart the application" << endl;
        return;
    }
    for (Movie movie : movielist)
    {
        tm movie_tm = movie.get_avaliable_to();
        tm movie_fm = movie.get_avaliable_from();

        fout << movie.get_id() << " " << movie.get_movie_name() << " "
             << setfill('0') << setw(2) << 1 + movie_fm.tm_mon << "-" << setfill('0') << setw(2) << movie_fm.tm_mday << "-" << (1900 + movie_fm.tm_year) << " "
             << setfill('0') << setw(2) << 1 + movie_tm.tm_mon << "-" << setfill('0') << setw(2) << movie_tm.tm_mday << "-" << (1900 + movie_tm.tm_year) << " " << movie.get_rating() << endl;
    }
    cout << "Movies updated in DB\n"
         << endl;

    fout.close();
}

void Utils::display_movies_using_stack()
{
    vector<Movie> movies = readMovieData(Movie::MOVIE_DATA_FILE);
    cout << "--------------------------------------------\n"
         << endl;

    MovieStack st;
    for (Movie movie : movies)
    {
        st.push(movie);
    }

    try
    {
        st.is_Empty();
        cout << "Movies that are currently showing in theatre\n"
             << endl;
        while (true)
        {
            cout << st.pop();
        }
    }
    catch (const MovieStack::StackEmptyException &e)
    {
        cout << e.what() << endl;
    }
    cout << "\n--------------------------------------------" << endl;
}
void Utils::add_movie_to_db()
{
    string filename;
    cout << "Please enter the file name : ";
    cin >> filename;
    cout << endl;
    vector<Movie> movies_to_add = readMovieData(filename);
    vector<Movie> existing_movies = readMovieData(Movie::MOVIE_DATA_FILE);
    vector<Movie> final_movies_to_add_in_db;
    for (Movie new_movie : movies_to_add)
    {
        bool found = false;
        for (Movie movie_in_db : existing_movies)
        {
            if (new_movie == movie_in_db)
            {
                cout << "Skipping to add " << new_movie.get_movie_name() << " as it already exists in db" << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            final_movies_to_add_in_db.push_back(new_movie);
        }
    }

    write_movie_to_file(final_movies_to_add_in_db, Movie::MOVIE_DATA_FILE, false);
}
bool Utils::isDateInRange(tm start, tm end)
{
    // Compare current date with the start and end dates
    auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm current = *localtime(&currentTime);
    return mktime(&current) >= mktime(&start) && mktime(&current) <= mktime(&end);
}
void Utils::book_ticket()
{
    tm TodayDate = getCurrentDate();
    tm TomorrowDate = getTomorrowDate();
    tm dayAfterTomorrowDate = getDayAfterTomorrowDate();
    vector<Movie> movies = readMovieData(Movie::MOVIE_DATA_FILE);
    vector<Movie> movies_to_show;
    for (Movie movie_i : movies)
    {
        tm from = movie_i.get_avaliable_from();
        tm to = movie_i.get_avaliable_to();
        if (isDateInRange(from, to) && mktime(&dayAfterTomorrowDate) <= mktime(&to))
        {
            movies_to_show.push_back(movie_i);
        }
    }
    if ((int)movies_to_show.size() == 0)
    {
        cout << "Sorry we are currently not accepting bookings for next 3 days" << endl;
        return;
    }
    int selected_movie_choice;
    do
    {
        cout << "------------select Movie------------" << endl;
        for (int i = 0; i < (int)movies_to_show.size(); i++)
        {
            cout << i + 1 << ". " << movies_to_show[i].get_movie_name() << endl;
        }
        cout << "Please select Movie : ";
        // cin >> selected_movie_choice;
        // cout << endl;

        if (!(cin >> selected_movie_choice))
        {
            // Clear the error state of cin
            cin.clear();
            // Ignore invalid input in the stream until a newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl;
    } while (selected_movie_choice < 1 || selected_movie_choice > (int)movies_to_show.size());

    cout << "The selected movie is rated as " << movies_to_show[selected_movie_choice - 1].get_rating_msg() << endl
         << endl;

    int selected_movie_id = movies_to_show[selected_movie_choice - 1].get_id();

    int selected_date_choice;
    do
    {
        cout << "1. ";
        printDate(TodayDate);
        cout << "2. ";
        printDate(TomorrowDate);
        cout << "3. ";
        printDate(dayAfterTomorrowDate);

        cout << "Please select date : ";
        // cin >> selected_date_choice;

        if (!(cin >> selected_date_choice))
        {
            // Clear the error state of cin
            cin.clear();
            // Ignore invalid input in the stream until a newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // cout << endl;
        cout << endl;

    } while (selected_date_choice > 3 || selected_date_choice < 1);

    tm selected_date = selected_date_choice == 1 ? TodayDate : selected_date_choice == 2 ? TomorrowDate
                                                                                         : dayAfterTomorrowDate;
    int selected_slot_choice;
    do
    {
        cout << "------------select ShowTime------------" << endl;
        cout << "1. 11AM" << endl;
        cout << "2. 2PM" << endl;
        cout << "3. 6PM" << endl;
        cout << "4. 9PM" << endl;
        cout << "Please select slot : ";
        // cin >> selected_slot_choice;
        if (!(cin >> selected_slot_choice))
        {
            // Clear the error state of cin
            cin.clear();
            // Ignore invalid input in the stream until a newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // cout << endl;
        cout << endl;
    } while (selected_slot_choice > 4 || selected_slot_choice < 1);

    string selected_slot = Utils::show_slots[selected_slot_choice - 1];
    int selected_no_of_tickets = 0;
    while (true)
    {
        cout << "Please enter number of tickets atleast 1 :";
        cin >> selected_no_of_tickets;
        cout << endl;
        if (selected_no_of_tickets > 0)
            break;
    }

    BookTicket ticket(selected_movie_id, selected_date, selected_slot, selected_no_of_tickets);
    ticket.validate_and_book_ticket();
}
tm Utils::getCurrentDate()
{
    auto currentTime = chrono::system_clock::now();
    time_t currentTimeT = chrono::system_clock::to_time_t(currentTime);
    tm currentDate = *localtime(&currentTimeT);
    currentDate.tm_year += 1900;
    currentDate.tm_mon += 1;
    return currentDate;
}
tm Utils::getTomorrowDate()
{
    // Get the current time point
    auto currentTime = chrono::system_clock::now();

    // Calculate tomorrow by adding 1 day (24 hours) to the current date
    chrono::hours oneDay(24);
    auto tomorrowTime = currentTime + oneDay;

    // Convert the time point for tomorrow to a time_t object
    time_t tomorrowTimeT = chrono::system_clock::to_time_t(tomorrowTime);

    // Convert the time_t object to a tm struct for tomorrow
    tm tomorrowDate = *localtime(&tomorrowTimeT);
    tomorrowDate.tm_year += 1900;
    tomorrowDate.tm_mon += 1;

    return tomorrowDate;
}
tm Utils::getDayAfterTomorrowDate()
{
    auto currentTime = chrono::system_clock::now();
    chrono::hours twoDays(48);
    auto dayAfterTomorrowTime = currentTime + twoDays;
    time_t dayAfterTomorrowTimeT = chrono::system_clock::to_time_t(dayAfterTomorrowTime);
    tm dayAfterTomorrowDate = *localtime(&dayAfterTomorrowTimeT);
    dayAfterTomorrowDate.tm_year += 1900;
    dayAfterTomorrowDate.tm_mon += 1;
    return dayAfterTomorrowDate;
}
void Utils::printDate(tm date)
{
    cout << (date.tm_year) << "-" << (date.tm_mon + 1) << "-" << date.tm_mday << endl;
}
vector<BookTicket> Utils::get_all_bookings()
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

int Utils::view_all_bookings_in_queue()
{
    BookingQueue q;
    vector<BookTicket> tickets = get_all_bookings();
    // if ((int)tickets.size() == 0)
    // {
    //     cout << "Currently there are no bookings" << endl;
    //     return 0;
    // }
    // heading display
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
    return 1;
}

void Utils::get_booking_info(bool isAdmin)
{
    Command *cmd;
    if (isAdmin)
        cmd = new AdminCommand;
    else
        cmd = new UserCommand;
    cmd->get_booking_info();
    // return 1;
}

void Utils::cancel_booking(string bookingID)
{
    vector<BookTicket> tickets = get_all_bookings();

    ofstream fout(BookTicket::BOOKINGS_FILE);
    bool ticket_found = false;
    bool show_heading = true;
    for (BookTicket ticket : tickets)
    {
        if (!(ticket == bookingID))
        {
            fout << ticket.tostring(show_heading);
        }
        else
        {
            ticket_found = true;
        }
        show_heading = false;
    }
    if (!ticket_found)
        cout << "Ticket not found with given booking id" << endl;
    else
        cout << "Booking cancelled successfully" << endl;

    fout.close();
}

void Utils::remove_movie_from_db(int movieId)
{
    vector<Movie> movies = readMovieData(Movie::MOVIE_DATA_FILE);
    vector<Movie> updated_movies_input;
    for (int i = 0; i < (int)movies.size(); i++)
    {
        if (movies[i].get_id() != movieId)
        {
            updated_movies_input.push_back(movies[i]);
        }
    }
    if (movies.size() == updated_movies_input.size())
    {
        cout << "Movie with given id not found in db" << endl;
    }
    else
    {
        write_movie_to_file(updated_movies_input, Movie::MOVIE_DATA_FILE, true);
    }
}
void Utils::update_movie_in_db(int movieId)
{
    vector<Movie> movies = readMovieData(Movie::MOVIE_DATA_FILE);
    bool found = true;
    for (int i = 0; i < (int)movies.size(); i++)
    {
        if (movies[i].get_id() == movieId)
        {
            string new_movie_name, avaliable_from, avaliable_to;
            char update_movie_name;
            cout << "Enter Y or y to update movie name: ";
            cin >> update_movie_name;
            cout << endl;
            if (update_movie_name == 'y' || update_movie_name == 'Y')
            {
                cout << "Enter the movie name to update :";
                cin >> new_movie_name;
                movies[i].set_movie_name(new_movie_name);
            }
            char update_movie_from_date;
            cout << "Enter Y or y to update movie from date: ";
            cin >> update_movie_from_date;
            cout << endl;
            if (update_movie_from_date == 'y' || update_movie_from_date == 'Y')
            {
                cout << "Enter the avaliable from date in MM-DD-YYYY format:";
                cin >> avaliable_from;
                cout << endl;
                movies[i].set_avaliable_from(BookTicket::get_date_from_string(avaliable_from));
            }
            char update_movie_to_date;
            cout << "Enter Y or y to update movie to date: ";
            cin >> update_movie_to_date;
            cout << endl;
            if (update_movie_to_date == 'y' || update_movie_to_date == 'Y')
            {
                cout << "Enter the avaliable from date in MM-DD-YYYY format:";
                cin >> avaliable_to;
                cout << endl;
                movies[i].set_avaliable_to(BookTicket::get_date_from_string(avaliable_to));
            }

            found = false;
            break;
        }
    }
    if (found)
    {
        cout << "Movie with given id not found in db" << endl;
    }
    else
    {
        write_movie_to_file(movies, Movie::MOVIE_DATA_FILE, true);
    }
}

void Utils::get_min_life_span_movie()
{
    MinHeap heap;
    vector<Movie> all_movies = readMovieData(Movie::MOVIE_DATA_FILE);
    if (all_movies.size() == 0)
    {
        cout << "Movies that are currently showing in theatre\n"
             << endl;
        return;
    }
    for (Movie movie : all_movies)
        heap.insert(movie);
    char next_min = 'y';
    // cout<<"------------------------------"<<endl;
    // cout<<"---Movie-----|--LifeSpan-------"<<endl;
    while (next_min == 'y' || next_min == 'Y')
    {
        try
        {
            Movie min_days_movie = heap.remove_min();
            // cout << "Movie with minimum life span in theatre is " << endl;
            cout << "Movie : " << min_days_movie.get_movie_name() << endl
                 << "Days : " << heap.get_days_in_two_dates(min_days_movie) << endl;
            cout << "Please enter y or Y to get next minimum life span movie" << endl;
            cin >> next_min;
        }
        catch (const MinHeap::MinHeapEmptyException &e)
        {
            cout << "Caught up with all movies!....\n"
                 << endl;
            break;
        }
    }
    return;
}