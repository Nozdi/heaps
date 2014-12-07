/**
    fibonacci.h
    Purpose: Declaring fibonacci heap type min

    @author Mateusz Flieger
    @version 1.0 4.12.2014
*/

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "node.h"
#include <iostream>
#include <cstddef>
#include <cmath>
#include <vector>
#include <limits>


class FibonacciHeap : public AbstractHeap {

private:
    void cut(Node *x, Node *y);
    void cascading_cut(Node *y);
    void heap_link(Node *y, Node *x);
    void consolidate();
    Node *min;
    int n;

public:
    Node* get_min();
    void set_min(Node* min);
    int get_n();
    void set_n(int n);

    FibonacciHeap();
    ~FibonacciHeap();

    void print();
    void insert(int key);
    int minimal();
    int extract_minimal();
    int decrease_key(int key, int value);
    int delete_key(int key);

};

FibonacciHeap* fib_union (FibonacciHeap *f1, FibonacciHeap *f2);

#endif //FIBONACCI_H
