#pragma once

using namespace std;

// Defines
#define WHITE 0
#define BLACK 1
#define EMPTY 2
#define SIZE  7

// Class Node
class Node {
public:
    Node(int* state, int hn) { 
        this->_state = state;
        this->_hn = hn;
    };

    ~Node() { 
        // Do nothing
    };

    int* get_state() {
        return this->_state;
    };

    int get_hn() {
        return this->_hn;
    }

private:
    int* _state;
    int _hn;
};

