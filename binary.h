/**
    binary.h
    Purpose: Declaring binary heap type min

    @author Mateusz Flieger
    @version 1.0 4.12.2014
*/

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include "abstract.h"
#include <vector>
#include <iostream>
#include <limits>


class BinaryHeap : public AbstractHeap {
    std::vector<int> table;
    int heap_size;
    void print_table();
    void insert_table(int elem);

public:
    BinaryHeap();

    void print();

    void heapify(int i);
    int parent(int i);
    int left(int i);
    int right(int i);

    int length();
    std::vector<int> get_table();
    void set_table(std::vector<int> table);
    void build();

    int minimal();
    int extract_minimal();
    int decrease_key(int key, int value);
    void insert(int key);
    int delete_key(int key);
};


BinaryHeap* bin_union(BinaryHeap *h1, BinaryHeap *h2);

#endif //BINARY_H
