#include "node.h"
#include "Movie.h"
#include <iostream>
using namespace std;
node::node(Movie data)
{
    this->data = data;
    this->next = NULL;
}