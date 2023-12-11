#ifndef DHEAP_H
#define DHEAP_H
#include <vector>
#include <iostream>
#include "Movie.h"
using namespace std;

class MinHeap
{
private:
    vector<Movie> elements; // vector for dynamic resizing

public:
    class MinHeapEmptyException
    {
    };
    MinHeap();
    // ~MinHeap();
    void insert(Movie &); // adds a new element to this heap
    Movie remove_min();   // removes the min element from the heap
    int size() const;     // returns the # of elements in the heap
    int get_days_in_two_dates(Movie);
};
#endif
