/**
    main.cpp
    Purpose: Main event loop for binary and fibonacci heap

    @author Mateusz Flieger
    @version 1.0 4.12.2014
*/

#include <iostream>
#include "abstract.h"
#include "binary.h"
#include "fibonacci.h"

using namespace std;


int char_to_int(char c){
    return (int)c - 48;
}


int get_heap(vector<AbstractHeap*> heaps) {
    char input;
    int choice;
    if ( heaps.size() < 1 ) {
        cout << "Create heap first!" << endl;
        return -1;
    }
    if ( heaps.size() == 1) return 1;
    while(true){
        cout << "Choose heap: " << endl;
        cout << "1.."<< heaps.size() << endl;
        cin >> input;
        choice = char_to_int(input);
        if (choice > 0 && choice <= heaps.size())
            break;
    }
    return choice;
}


int main(void){
    int type;
    char input;
    bool choosen = false;
    while(!choosen){
        cout << "Choose priority queue type:" << endl;
        cout << "1 - binary heap" << endl;
        cout << "2 - fibonacci heap" << endl;
        cout << "3 - exit" << endl;
        cin >> input;
        type = char_to_int(input);
        switch(type){
            case 1: case 2:
                choosen = true;
                break;
            case 3:
                return 0;
            default:
                cout << "Wrong choice" << endl;
                break;
        }
    }
    int option, no, first, sec;
    vector<AbstractHeap*> heaps;

    while(true){
        cout << "Operations on heap:" << endl;
        cout << "1 - make heap" << endl;
        cout << "2 - insert element" << endl;
        cout << "3 - extract min" << endl;
        cout << "4 - min" << endl;
        cout << "5 - decrease node by key" << endl;
        cout << "6 - union heaps" << endl;
        cout << "7 - delete" << endl;
        cout << "8 - display heap" << endl;
        cout << "9 - exit" << endl;

        cin >> input;
        option = char_to_int(input);

        switch(option){
            case 1: {
                if ( type == 1 ){
                    heaps.push_back(new BinaryHeap);
                }else{
                    heaps.push_back(new FibonacciHeap);
                }
                break;
            }case 2: {
                int l;
                no = get_heap(heaps);
                if ( no < 0 ) break;
                cout << "Positive integer to insert: ";
                cin >> l;
                if (l > 0 ){
                    heaps[no-1]->insert(l);
                }
                else {
                    cout << "Positive integer must be > 0" << endl;
                }
                break;
            }case 3: {
                no = get_heap(heaps);
                if ( no < 0 ) break;
                int min = heaps[no-1]->extract_minimal();
                if ( min < 0 ){
                    cout << "Heap too small!" << endl;
                    break;
                }
                cout << "Min: " << min << endl;
                break;
            }case 4:{
                no = get_heap(heaps);
                if ( no < 0 ) break;
                int minimal = heaps[no-1]->minimal();
                if ( minimal < 0 ){
                    cout << "Heap too small!" << endl;
                    break;
                }
                cout << "Min: " << minimal << endl;
                break;
            }case 5: {
                no = get_heap(heaps);
                if ( no < 0 ) break;

                int k, v;
                cout << "Where (table id (binary) or key value (fib): ";
                cin >> k;
                cout << "What: ";
                cin >> v;
                int local_status = heaps[no-1]->decrease_key(k, v);
                if ( local_status == -1 ){
                    cout << "There is no such a key in heap!" << endl;
                }else if ( local_status == -1 ){
                    cout << "New value is bigger than acutal" << endl;
                }
                break;
            }case 6: {
                if ( heaps.size() == 1 ){
                    cout << "U need at least 2 heaps to make union" << endl;
                    break;
                }
                cout << "First: " << endl;
                first = get_heap(heaps);
                if (first < 0 ) break;
                cout << "Second: " << endl;
                sec = get_heap(heaps);
                if (sec < 0 ) break;
                if ( first == sec ){
                    cout << "Error! Cannot union same heaps";
                }
                else{
                    AbstractHeap *new_heap;

                    if (type == 1){
                        new_heap = bin_union(
                            (BinaryHeap*)heaps[first-1],
                            (BinaryHeap*)heaps[sec-1]
                        );
                    }else {
                        new_heap = fib_union(
                            (FibonacciHeap*)heaps[first-1],
                            (FibonacciHeap*)heaps[sec-1]
                        );
                    }

                    if (first > sec){
                        heaps.erase(heaps.begin() + (first-1));
                        heaps.erase(heaps.begin() + (sec-1));
                    } else {
                        heaps.erase(heaps.begin() + (sec-1));
                        heaps.erase(heaps.begin() + (first-1));
                    }

                    heaps.push_back(new_heap);
                    cout << "New heap is on: " << heaps.size() << " position" << endl;
                }
                break;
            }case 7:{
                no = get_heap(heaps);
                if ( no < 0 ) break;
                cout << "For binary index for fib value: ";
                int value;
                cin >> value;
                int local_status = heaps[no-1]->delete_key(value);
                if ( local_status == -1 )
                    cout << "Error! There is not such an element in heap!" << endl;
                break;
            }case 8: {
                no = get_heap(heaps);
                if ( no < 0 ) break;
                heaps[no-1]->print();
                break;
            }case 9: {
                return 0;
            }default: {
                cout << "Wrong choice" << endl;
                break;
            }
        }

    }
    for(int i=0; i<heaps.size(); i++){
        delete heaps[i];
    }
    return 0;
}
