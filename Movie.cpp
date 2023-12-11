#include <iostream>
#include <iomanip>
#include <fstream>
#include "Utils.h"
#include "Movie.h"
using namespace std;
const string Movie::MOVIE_DATA_FILE = "movies_in_application.txt";
Movie::Movie() {}
Movie::Movie(int id, string name, tm a_from, tm a_to, string rating)
{
    this->id = id;
    this->movie_name = name;
    this->avaliable_from = a_from;
    this->avaliable_to = a_to;
    this->rating = rating;
}
int Movie::get_id() const
{
    return this->id;
}
string Movie::get_movie_name() const
{
    return this->movie_name;
}
tm Movie::get_avaliable_from() const
{
    return this->avaliable_from;
}
tm Movie::get_avaliable_to() const
{
    return this->avaliable_to;
}
void Movie::set_id(int id)
{
    this->id = id;
}
void Movie::set_movie_name(string movie_name)
{
    this->movie_name = movie_name;
}
void Movie::set_avaliable_from(tm avaliable_from)
{
    this->avaliable_from = avaliable_from;
}
void Movie::set_avaliable_to(tm avaliable_to)
{
    this->avaliable_to = avaliable_to;
}
string Movie::get_rating() const
{
    return rating;
}
string Movie::get_rating_msg() const
{
    string s;
    string res = rating + " : ";
    for (auto &x : rating)
    {
        s += tolower(x);
    }
    if (s == "g")
    {
        res += "All ages admitted";
    }
    else if (s == "pg")
    {
        res += "Parental guidance suggested - some material may not be suitable for children";
    }
    else if (s == "pg-13")
    {
        res += "Parents strongly cautioned-some material may be inappropriate for children under 13";
    }
    else if (s == "r")
    {
        res += "Restricted under 17- requires accompanying parent or adult guardian";
    }
    else if (s == "nc-17")
    {
        res += "Clearly adult";
    }
    else
    {
        res += "This movie is not rated";
    }

    return res;
}

bool Movie::operator==(const Movie &rhs) const
{
    return this->get_movie_name() == rhs.get_movie_name();
}

ostream &operator<<(ostream &os, const Movie &movie)
{
    tm movie_tm = movie.get_avaliable_to();
    tm movie_fm = movie.get_avaliable_from();

    os << movie.get_id() << " "
       << setw(15) << left << movie.get_movie_name() << " ";

    // Set fill character to space ' ' for the date components
    os << setfill(' ');
    os << setw(2) << 1 + movie_fm.tm_mon << "-" << setw(2) << movie_fm.tm_mday << "-" << (1900 + movie_fm.tm_year) << " ";
    os << setw(2) << 1 + movie_tm.tm_mon << "-" << setw(2) << movie_tm.tm_mday << "-" << (1900 + movie_tm.tm_year) << endl;

    return os;
}