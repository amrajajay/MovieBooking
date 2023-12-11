#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <vector>
#include "Utils.h"
using namespace std;
class Movie
{

private:
    int id;
    string movie_name;
    tm avaliable_from;
    tm avaliable_to;
    string rating;

public:
    const static string MOVIE_DATA_FILE;
    Movie();
    Movie(int, string, tm, tm, string);
    int get_id() const;
    string get_movie_name() const;
    tm get_avaliable_from() const;
    tm get_avaliable_to() const;
    string get_rating() const;
    string get_rating_msg() const;
    void set_id(int);
    void set_movie_name(string);
    void set_avaliable_from(tm);
    void set_avaliable_to(tm);
    bool operator==(const Movie &) const;
    friend ostream &operator<<(ostream &, const Movie &);
};
#endif