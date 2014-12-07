/**
    fibonacci.cpp
    Purpose: Implementing fibonacci heap type min methods

    @author Mateusz Flieger
    @version 1.0 4.12.2014
*/

#include "fibonacci.h"


FibonacciHeap::FibonacciHeap() : min(NULL), n(0){}


FibonacciHeap::~FibonacciHeap(){
    for(int i=0; i<n; i++){
        extract_minimal();
    }
}


Node* FibonacciHeap::get_min(){
    return min;
}


void FibonacciHeap::set_min(Node* min){
    this->min = min;
}


int FibonacciHeap::get_n(){
    return n;
}


void FibonacciHeap::set_n(int n){
    this->n = n;
}


int FibonacciHeap::minimal(){
    if ( min != NULL )
        return min->key;
    return -1;
}


std::vector<Node*> print_helper(Node *start){
    std::vector<Node*> children;
    if ( start != NULL ) {
        Node *pom = start;
        int i=0;
        do {
            std::cout << " "<< pom->key << " ";
            children.push_back(pom->child);
            pom = pom->left;
            i++;
            if ( i ==10) break;
        } while ( pom != start );
    }
    return children;
}


bool children(std::vector<Node*> children) {
    for(int i=0; i<children.size(); ++i) {
        if ( children[i] != NULL )
            return true;
    }
    return false;
}


void FibonacciHeap::print(){
    std::vector<Node*> start, middle, append;
    start = print_helper(min);
    std::cout << std::endl;
    while (start.size() > 0 && children(start)) {
        middle.clear();
        for(int i=0; i<start.size(); i++){
            std::cout << "|";

            if ( start[i] !=NULL && start[i]->parent != NULL )
                std::cout << " parent: " << (start[i]->parent)->key << " " << "children: ";

            append = print_helper(start[i]);
            middle.insert( middle.end(), append.begin(), append.end() );
        }
        std::cout << std::endl;
        start = middle;
    }
}


void FibonacciHeap::insert(int key){
    Node *x = new Node;
    x->degree = 0;
    x->parent = NULL;
    x->child = NULL;
    x->marked = false;
    x->key = key;
    if ( min == NULL ) {
        x->left = x;
        x->right = x;
        min = x;
    }
    else {
        insert_left(min, x);
        if ( x->key < min->key ){
            min = x;
        }
    }
    n += 1;
}


int FibonacciHeap::extract_minimal(){
    Node *z = min;
    if ( min != NULL ) {
        Node *pom = min->child;
        if ( pom != NULL) {
            do {
                Node *current = pom;
                pom = pom->left;
                insert_left(min, current);
            } while ( pom != min->child );
            min->child = NULL;
        }
        remove_node(min);

        if (z == z->right)
            min = NULL;
        else{
            min = z->right;
            consolidate();
        }
        n -= 1;
    }
    int key = z->key;
    delete z;
    return key;
}


void FibonacciHeap::heap_link(Node *y, Node *x){
    remove_node(y);
    insert_child(x, y);
    x->degree += 1;
    y->marked = false;
}


void FibonacciHeap::consolidate(){
    int d_fib = int(log2(n));
    int d;
    typedef Node* NodePtr;
    NodePtr *tab = new NodePtr[d_fib+1];

    for(int i=0; i<=d_fib; i++){
        tab[i] = NULL;
    }
    Node *w = min;
    Node *x, *y, *swaper, *last;
    last = min;
    do {
        x = w;
        w = w->right;
        d = x->degree;
        while ( tab[d] != NULL ) {
            y = tab[d];
            if ( x->key > y->key ) {
                swaper = x;
                x = y;
                y = swaper;
            }
            if ( y == last )
                last = x;
            if ( w == y )
                w=w->right;
            heap_link(y, x);
            tab[d] = NULL;
            d += 1;
        }
        tab[d] = x;
    } while(w != last);
    min = NULL;
    for (int i=0; i<=d_fib; ++i) {
        if ( tab[i] != NULL ){
            if ( min == NULL ){
                min = tab[i];
                min->left = min;
                min->right = min;
            }
            else {
                insert_left(min, tab[i]);
                if ( tab[i]->key < min->key )
                    min = tab[i];
            }
        }
    }
    delete []tab;
}


int FibonacciHeap::decrease_key(int key, int value){
    // bigger than actual
    if ( value > key )
        return -2;
    Node *key_node = find_node(key, min);
    // no such a key in heap
    if ( key_node == NULL )
        return -1;

    key_node->key = value;
    Node *y = key_node->parent;

    if ( y != NULL && key_node->key < y->key) {
        cut(key_node, y);
        cascading_cut(y);
    }

    if ( key_node->key < min->key )
        min = key_node;
    return 0;
}


void FibonacciHeap::cut(Node *x, Node *y){
    int status = remove_node(x);
    y->degree -= 1;

    if ( y->child == x )
        y->child = (y->child)->left;

    if ( status == -1 )
        y->child = NULL;

    insert_left(min, x);
    x->parent = NULL;
    x->marked = false;
}


void FibonacciHeap::cascading_cut(Node *y){
    Node *z = y->parent;
    if ( z != NULL ){
        if ( y->marked == false ){
            y->marked = true;
        }
        else {
            cut(y, z);
            cascading_cut(z);
        }
    }
}


FibonacciHeap* fib_union (FibonacciHeap *f1, FibonacciHeap *f2){
    // if any of heaps is empty
    if ( f1->get_min() == NULL )
        return f2;

    if ( f2->get_min() == NULL )
        return f1;

    // otherwise
    FibonacciHeap *new_heap = new FibonacciHeap();
    new_heap->set_min(concatenate_lists(f1->get_min(), f2->get_min()));

    if ( (f1->get_min() == NULL) ||
        (f2->get_min() != NULL && (new_heap->get_min()) < f1->get_min()) ){

        new_heap->set_min(f2->get_min());
    }

    new_heap->set_n(f1->get_n() + f2->get_n());
    return new_heap;
}


int FibonacciHeap::delete_key(int key){
    int status = decrease_key(key, std::numeric_limits<int>::min());
    if ( status == 0 )
        extract_minimal();
    return status;
}

