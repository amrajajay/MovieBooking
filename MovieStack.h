#ifndef MOVIESTACK_H
#define MOVIESTACK_H
#include "node.h"
#include "Movie.h"
#include <iostream>
using namespace std;
struct MovieStack
{
public:
    class StackEmptyException:exception {
        private:
         const char* message;
        public:
         StackEmptyException(const char* msg) : message(msg) {}
        const char* what() const noexcept override {
            return message;
        }

    };
    MovieStack();
    node *top;
    void push(Movie);
    Movie pop();
    bool is_Empty();
    ~MovieStack();
};
#endif