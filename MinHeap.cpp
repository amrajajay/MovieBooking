#include <iostream>
#include <iomanip>
#include "MinHeap.h"
using namespace std;
MinHeap::MinHeap()
{
    Movie dummy;
    elements.push_back(dummy);
}

void MinHeap::insert(Movie &new_movie)
{
    elements.push_back(new_movie);
    if (size() == 1)
        return;
    int pos = size();
    while (pos > 1 && get_days_in_two_dates(elements[pos / 2]) > get_days_in_two_dates(new_movie))
    {
        elements[pos] = elements[pos / 2];
        pos = pos / 2;
    }
    elements[pos] = new_movie;
}
int MinHeap::size() const // returns the # of elements in the heap
{
    return this->elements.size() - 1;
}
int MinHeap::get_days_in_two_dates(Movie movie)
{
    tm date1 = movie.get_avaliable_from();
    tm date2 = movie.get_avaliable_to();
    time_t time_from = mktime(const_cast<tm *>(&date1));
    time_t time_to = mktime(const_cast<tm *>(&date2));
    //  timeFromTm(date2);
    const int seconds_per_day = 60 * 60 * 24;
    time_t difference = std::difftime(time_to, time_from);

    return difference / seconds_per_day;
}

Movie MinHeap::remove_min() // removes the min element from the heap
{
    int len = size();
    if (len == 0)
        throw MinHeapEmptyException();
    Movie min_ele = elements[1];
    elements[1] = elements[size()];
    elements.pop_back();
    len -= 1;

    int parent = 1;
    int left = 2, right = 3;
    Movie root = elements[parent];
    while (left <= len)
    {
        int index = left;
        if (right <= len)
            index = get_days_in_two_dates(elements[left]) <= get_days_in_two_dates(elements[right]) ? left : right;

        if (get_days_in_two_dates(elements[parent]) > get_days_in_two_dates(elements[index]))
        {
            elements[parent] = elements[index];
            elements[index] = root;
            parent = index;
        }
        else
            break;
        left = parent * 2;
        right = left + 1;
        root = elements[parent];
    }
    return min_ele;
}

time_t timeFromTm(tm &time)
{
    return std::mktime(const_cast<tm *>(&time));
}