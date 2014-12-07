/**
    binary.cpp
    Purpose: Implementing binary heap type min methods

    @author Mateusz Flieger
    @version 1.0 4.12.2014
*/

#include "binary.h"


BinaryHeap::BinaryHeap() : table(1), heap_size(0) {
    build();
}


void BinaryHeap::print(){
    for(int i=1; i<=heap_size; i++){
        std::cout << table[i] << " ";
    }
    std::cout << std::endl;
}


void BinaryHeap::print_table(){
    for(int i=1; i<=table.size(); i++){
        std::cout << table[i] << " ";
    }
    std::cout << std::endl;
}


int BinaryHeap::parent(int i){
    return i/2;
}


int BinaryHeap::left(int i){
    return 2*i;
}


int BinaryHeap::right(int i){
    return 2*i+1;
}


int BinaryHeap::length(){
    return heap_size;
}


/**
    Inserts element to table (not treated as a heap).

    @param elem - int to be iserted.
*/
void BinaryHeap::insert_table(int elem){
    table.push_back(elem);
    heap_size += 1;
}


void BinaryHeap::heapify(int i){
    int l, r, smallest;
    l = left(i);
    r = right(i);
    if ( l <= heap_size && table[l] < table[i] ){
        smallest = l;
    }
    else {
        smallest = i;
    }
    if ( r <= heap_size && table[r] < table[smallest] ){
        smallest = r;
    }
    if ( smallest != i ){
        int pom;
        pom = table[i];
        table[i] = table[smallest];
        table[smallest] = pom;
        heapify(smallest);
    }
}


void BinaryHeap::build(){
    heap_size = table.size() - 1;
    for(int i=(table.size()-1)/2; i>=1; i--){
        heapify(i);
    }
}


int BinaryHeap::minimum(){
    return table[1];
}


int BinaryHeap::extract_minimal(){
    int min;
    if ( heap_size < 1 ){
        return -1; // error heap is empty
    }
    min = table[1];
    table[1] = table[heap_size];
    heap_size -= 1;
    heapify(1);
    return min;
}


int BinaryHeap::delete_key(int key){
    if ( heap_size < 1 ){
        return -1; // error heap is empty
    }
    table[key] = table[heap_size];
    heap_size -= 1;
    heapify(key);
    return 0;
}


int BinaryHeap::decrease_key(int key, int value){
    int pom;
    if ( key > heap_size ){
        return -1; // too big i
    }
    if ( value > table[key] ) {
        return -2; // value is bigger than actual
    }
    table[key] = value;
    while ( key > 1 && table[parent(key)] > table[key] ){
        pom = table[key];
        table[key] = table[parent(key)];
        table[parent(key)] = pom;
        key = parent(key);
    }
    return 0;
}


void BinaryHeap::insert(int key){
    heap_size += 1;
    if ( heap_size > (table.size() - 1) ){
        table.push_back(std::numeric_limits<int>::max());
    }
    else{
        table[heap_size] = std::numeric_limits<int>::max();
    }
    decrease_key(heap_size, key);
}


std::vector<int> BinaryHeap::get_table(){
    return table;
}


void BinaryHeap::set_table(std::vector<int> table){
    this->table = table;
}



BinaryHeap* bin_union(BinaryHeap *h1, BinaryHeap *h2){
    std::vector<int> table1, table2;
    BinaryHeap *new_h = new BinaryHeap();
    table1 = h1->get_table();
    table2 = h2->get_table();
    table1.insert( table1.end(), table2.begin()+1, table2.end() );

    new_h->set_table(table1);
    new_h->build();
    return new_h;
}


