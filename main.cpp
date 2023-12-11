#include <iostream>
#include <cassert>
#include <conio.h>
#include "Utils.h"
#include "MovieStack.h"
MovieStack movie_stack;
using namespace std;

void run_main_menu();
void run_admin_menu();
bool verify_as_admin();
string takePasswdFromUser();
int main()
{
    run_main_menu();
}
void run_main_menu()
{
    int choice;
    do
    {
        cout << "------------Main Menu------------" << endl;
        cout << "1. Access Admin console" << endl;
        cout << "2. View Movies" << endl;
        cout << "3. Book a ticket" << endl;
        cout << "4. View Booking information by Booking Id" << endl;
        cout << "5. Cancel Booking" << endl;
        cout << "6. Exit" << endl;
        cout << "-----------Main Menu-------------" << endl;

        while (true)
        {
            cout << "Enter your choice: " << endl;
            cin >> choice;
            if (choice == 1)
            {
                run_admin_menu();
                break;
            }
            else if (choice == 2)
            {
                Utils::display_movies_using_stack();
                break;
            }
            else if (choice == 3)
            {
                Utils::book_ticket();
                break;
            }
            else if (choice == 4)
            {

                Utils::get_booking_info(false);
                break;
            }
            else if (choice == 5)
            {
                cout << "Please enter booking id: ";
                string bookingId;
                cin >> bookingId;
                cout << endl;
                Utils::cancel_booking(bookingId);
                break;
            }
            else if (choice == 6)
            {
                cout << "Thank You\nVisit again";
                exit(0);
            }
            else
            {
                cout << "Invalid Choice" << endl;
                break;
            }
        }
    } while (true);
}

void run_admin_menu()
{
    if (!verify_as_admin())
    {
        cout << "You are not authorized to access admin console." << endl;
        return;
    }
    do
    {
        int choice;
        cout << "-----------Admin Menu-------------" << endl;
        cout << "1. View existing movies" << endl;
        cout << "2. Add a movie to db" << endl;
        cout << "3. Remove a movie from db" << endl;
        cout << "4. Update movie details" << endl;
        cout << "5. View all bookings" << endl;
        cout << "6. Get movie with lowest life span" << endl;
        cout << "7. Go back to main menu" << endl;
        cout << "8. Exit from application" << endl;
        cout << "----------Admin Menu--------------" << endl;

        while (true)
        {
            cout << "Enter your choice: " << endl;
            cin >> choice;
            if (choice == 1)
            {
                Utils::display_movies_using_stack();
                break;
            }
            else if (choice == 2)
            {
                Utils::add_movie_to_db();
                break;
            }
            else if (choice == 3)
            {
                int movie_id;
                cout << "Please enter the movie id which you want to delete from db: ";
                cin >> movie_id;
                cout << endl;
                Utils::remove_movie_from_db(movie_id);
                break;
            }
            else if (choice == 4)
            {
                int movie_id;
                cout << "Please enter the movie id which you want to update from db: ";
                cin >> movie_id;
                cout << endl;
                Utils::update_movie_in_db(movie_id);
                break;
            }
            else if (choice == 5)
            {
                Utils::get_booking_info(true);
                break;
            }
            else if (choice == 6)
            {
                Utils::get_min_life_span_movie();
                break;
            }
            else if (choice == 7)
            {
                return;
            }
            else if (choice == 8)
            {
                cout << "Thank You\nVisit again";
                exit(0);
            }
            else
            {
                cout << "Invalid Choice" << endl;
                break;
            }
        }
    } while (true);
}

bool verify_as_admin()
{
    string user, password;

    int chances = 3;
    while (chances--)
    {
        if (chances < 0)
        {
            return false;
        }

        cout << "Please enter user name: ";
        cin >> user;
        cout << endl;
        cout << "Please enter password: ";
        password = takePasswdFromUser();
        cout << endl;

        if (user == "admin" && password == "admin")
        {
            cout << endl;
            return true;
        }
        cout << "Invalid user name or password\n\nYou have " << chances << " chances left\n"
             << endl;
    }
    return false;
}

string takePasswdFromUser()
{
    string ipt = "";

    char ipt_ch;

    while (true)
    {
        ipt_ch = getch();

        cout << "\033[1m*\033[0m";
        if (ipt_ch < 32)
        {
            cout << endl;
            return ipt;
        }

        ipt.push_back(ipt_ch);
    }
}