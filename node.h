#ifndef NODE_H
#define NODE_H
#include "Movie.h"
struct node
{
    Movie data;
    node *next;
    // node();
    node(Movie);
};
#endif