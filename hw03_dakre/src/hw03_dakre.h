#pragma once
#include <cstring>
#include <array>

using namespace std;

// Defines
#define WHITE 0
#define BLACK 1
#define EMPTY 2
#define SIZE  7

// Class Node
class Node {
public:
    Node(array<int, SIZE> state, int hn, int cost) :
      _state(state), 
      _hn(hn),
      _cost(cost),
      _visited(false) { 
        // Do nothing
    };

    ~Node() { 
        // Do nothing
    };

    array<int, SIZE> getState() {
        return this->_state;
    };

    int getHn() {
        return this->_hn;
    }

    int getCost() {
        return this->_cost;
    }

    void setVisited() {
        this->_visited = true;
    }

    bool getVisited() {
        return this->_visited;
    }

private:
    array<int, SIZE> _state;
    int _hn;
    int _cost;
    bool _visited;
};

