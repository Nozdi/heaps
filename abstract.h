/**
    fibonacci.h
    Purpose: Declaring fibonacci heap type min

    @author Mateusz Flieger
    @version 1.0 4.12.2014
*/

#ifndef ABSTRACT_H
#define ABSTRACT_H

class AbstractHeap {

public:
    virtual ~AbstractHeap();
    virtual void print() = 0;
    virtual void insert(int key) = 0;
    virtual int extract_minimal() = 0;
    virtual int decrease_key(int key, int value) = 0;
    virtual int delete_key(int key) = 0;
};

inline AbstractHeap::~AbstractHeap() { }

#endif //ABSTRACT_H
