/**
    fibonacci.h
    Purpose: Declaring nodes for fibonacci heap and it's functions

    @author Mateusz Flieger
    @version 1.0 4.12.2014
*/

#ifndef NODE_H
#define NODE_H

#include <cstddef>


struct Node {
    struct Node *left;
    struct Node *right;
    struct Node *child;
    struct Node *parent;
    int key;
    int degree;
    bool marked;
};

void insert_left(Node *from, Node *n);
int remove_node(Node *to_remove);
Node* concatenate_lists(Node *l1, Node *l2);
void insert_child(Node *x, Node *child);
Node* find_node(int key,  Node* start);

#endif //NODE_H
