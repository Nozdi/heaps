#include "node.h"


void insert_left(Node *from, Node *n){
    Node *pom = from->left;
    from->left = n;
    n->left = pom;
    n->right = from;
    pom->right = n;
}


int remove_node(Node *to_remove){
    Node *left_node = to_remove->left;
    Node *right_node = to_remove->right;

    left_node->right = right_node;
    right_node->left = left_node;

    // removed last one
    if (left_node == to_remove ){
        return -1;
    }
    return 0;
}


Node* concatenate_lists(Node *l1, Node *l2){
    Node *concatenated, *pom;

    concatenated = l1;
    (concatenated->left)->right = l2;
    (l2->left)->right = concatenated;
    pom = concatenated->left;
    concatenated->left = l2->left;
    l2->left = pom;

    return concatenated;
}


void insert_child(Node *x, Node *child){
    if ( x->child == NULL ){
        x->child = child;
        child->left = child;
        child->right = child;
    }
    else{
        insert_left(x->child, child);
    }
    child->parent = x;
}


Node* find_node(int key,  Node* start){
    Node *pom, *iterator=start;
    do {
        if ( iterator->key == key ) {
            return iterator;
        }
        if ( iterator->child != NULL ){
             pom = find_node(key, iterator->child);
             if ( pom != NULL ){
                return pom;
             }
        }
        iterator = iterator->left;
    } while ( iterator != start );
    return NULL;
}
