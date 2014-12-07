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


int get_heap(vector<AbstractHeap*> heaps){
    int choice;
    if ( heaps.size() < 1 ) {
        cout << "Create heap first!";
        return -1;
    }
    while(true){
        cout << "Choose heap: " << endl;
        cout << "1.."<< heaps.size() << endl;
        cin >> choice;
        if (choice > 0 && choice <= heaps.size()){
            break;
        }
    }
    return choice;
}


int main(void){
    int type;
    bool choosen = false;
    while(!choosen){
        cout << "Choose heap type:" << endl;
        cout << "1 - binary heap" << endl;
        cout << "2 - fibonacci heap" << endl;
        cout << "3 - exit" << endl;
        cin >> type;
        switch(type){
            case 1: case 2:
                choosen = true;
                break;
            case 3:
                exit(0);
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
        cout << "4 - decrease node by key" << endl;
        cout << "5 - union heaps" << endl;
        cout << "6 - display heap" << endl;
        cout << "7 - exit" << endl;
        cin >> option;
        switch(option){
            case 1: {
                if ( type == 1){
                    heaps.push_back(new BinaryHeap);
                }else{
                }
                break;
            }case 2: {
                int l;
                no = get_heap(heaps);
                if ( no < 0 ) break;
                cout << "Natural number to insert: ";
                cin >> l;
                if (l > 0 ){
                    heaps[no-1]->insert(l);
                }
                else {
                    cout << "Natural must be > 0" << endl;
                }
                break;
            }case 3: {
                no = get_heap(heaps);
                if ( no < 0 ) break;
                cout << heaps[no-1]->extract_minimal();
                break;
            }case 4: {
                no = get_heap(heaps);
                if ( no < 0 ) break;

                int k, v;
                cout << "Where: ";
                cin >> k;
                cout << "What: ";
                cin >> v;
                heaps[no-1]->decrease_key(k, v);
                break;
            }case 5: {
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
                    if (type == 1){
                        // Deletes the second element (vec[1])

                        BinaryHeap *new_heap = bin_union(
                            (BinaryHeap*)heaps[first-1],
                            (BinaryHeap*)heaps[sec-1]
                        );
                        if (first > sec){
                            heaps.erase(heaps.begin() + (first-1));
                            heaps.erase(heaps.begin() + (sec-1));
                        } else{
                            heaps.erase(heaps.begin() + (sec-1));
                            heaps.erase(heaps.begin() + (first-1));
                        }
                        heaps.push_back(new_heap);
                        cout << "New heap is on: " << heaps.size() << " position" << endl;
                    }
                }
                break;
            }case 6: {
                no = get_heap(heaps);
                if ( no < 0 ) break;
                heaps[no-1]->print();
                break;
            }case 7: {
                exit(0);
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
