#ifndef BOOKINGQUEUE_H
#define BOOKINGQUEUE_H
#include "BookTicket.h"
#include "BookingNode.h"
#include <iostream>
using namespace std;
struct BookingQueue
{
    BookingNode *front;
    BookingNode *back;
    BookingQueue();
    void enQueue(BookTicket);
    void deQueue();
    ~BookingQueue();
    bool view();
    string peek();
    class QueueEmptyException:exception {
        private:
         const char* message;
        public:
         QueueEmptyException(const char* msg) : message(msg) {}
        const char* what() const noexcept override {
            return message;
        }

    };
};
#endif