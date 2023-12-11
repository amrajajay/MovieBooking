#include "MovieStack.h"
#include "node.h"
#include "Movie.h"
#include <iostream>
using namespace std;

MovieStack::MovieStack()
{
    this->top = NULL;
}

void MovieStack::push(Movie movie)
{
    node *temp = new node(movie);
    temp->next = top;
    top = temp;
}
Movie MovieStack::pop()
{
    if (top == NULL)
    {
        throw StackEmptyException("");
    }
    Movie value = top->data;
    node *temp = top;
    top = top->next;
    delete temp;
    return value;
}
bool MovieStack::is_Empty()
{
    if (top == NULL)
    {
        throw StackEmptyException("Currently there are no movies avaliable for steaming");
    }
    return true;
}
MovieStack::~MovieStack()
{
    while (top != NULL)
    {
        node *temp = top;
        top = top->next;
        delete temp;
    }
}
