#include "BookingNode.h"
#include "BookingQueue.h"
#include <iostream>
using namespace std;
BookingQueue::BookingQueue()
{
    this->front = NULL;
    this->back = NULL;
}
void BookingQueue::enQueue(BookTicket value)
{
    BookingNode *new_node = new BookingNode(value);
    if (back == NULL)
    {
        back = new_node;
        front = new_node;
        front->next = back;
        front->prev = back;
        back->prev = front;
        back->next = front;
    }
    else
    {
        back->next = new_node;
        new_node->prev = back;
        back = back->next;
        back->next = front;
        front->prev = back;
    }
}
void BookingQueue::deQueue()
{

    if (front == NULL)
    {
        throw QueueEmptyException("Queue is Empty");
    }

    // BookingNode *temp = front;
    // front = front->next;
    // front->prev = temp->prev;
    // front->prev->next = front;
    // // value = temp->data;
    // cout << temp->data.tostring(false);
    // // ticket = temp->data;
    // delete temp;

    BookingNode *temp = front;
    // BookingData dequeuedData = temp->data; // Store the data before deletion

    if (front == back)
    {
        // If only one element in the queue, set both front and back to NULL after deletion
        front = NULL;
        back = NULL;
    }
    else
    {
        front = front->next;
        front->prev = NULL;
    }
    cout << temp->data.tostring(false);
    delete temp;
    // return dequeuedData;
}
bool BookingQueue::view()
{

    if (front == NULL)
    {
        throw QueueEmptyException("Currently there are no bookings in the system");
    }
    return true;
}
string BookingQueue::peek()
{
    if (front == NULL)
    {
        throw QueueEmptyException("Queue is Empty\n");
        // return  ;
    }

    return front->data.tostring(false);
}
BookingQueue::~BookingQueue()
{
    // while (front != NULL)
    // {

    //     BookingNode *temp = front;
    //     if (front != back)
    //     {
    //         front = front->next;
    //         front->prev = temp->prev;
    //         front->prev->next = front;
    //     }
    //     delete temp;
    // }

    while (front != NULL)
    {

        BookingNode *temp = front;
        front = front->next;
        if (front != NULL)
        {

            front->prev = NULL;
            // front->prev->next = front;
        }
        else
        {
            back = NULL;
        }
        delete temp;
    }
}