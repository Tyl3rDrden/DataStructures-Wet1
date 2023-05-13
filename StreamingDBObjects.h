#ifndef _StreamingDBObjects_H
#define _StreamingDBObjects_H
#include <exception>
#include <stdexcept>
// Here I am defining all the classes and structs needed for the code to work

struct CompareIDFunctor {
    bool RightIdisBigger(int a, int b) {
        if (a == b) {
            throw std::invalid_argument("Identical Id's");
        }
        return a > b;
    }
};

#endif
