#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <queue>
#include <list>
#include <map>

// Definition of operators
#define NOPERATORS 6
#define EMPTYA     0
#define EMPTYB     1 
#define FILLA      2
#define FILLB      3
#define POURAB     4
#define POURBA     5

using namespace std;

class SearchSpace {
public:
    SearchSpace(int num_vertices, map<pair<int, int>, bool> states) {
        this->_num_vertices = num_vertices;
        //this->_adj_pair = new list<pair<int, int> >[num_vertices];
        this->_states = states; 
    };

    ~SearchSpace() { 
        // Do nothing
    };

    /*void addEdge(int index, pair<int, int> state) {
        this->_adj_pair[index].push_back(state);
    };*/

    void bfs(pair<int, int> state) {
        // Forward declarations
        pair<int, int> curr_state = state;
        queue<pair<int, int> > path;
        map<pair<int, int> bool> pot_states;
        map<pair<int, int>, bool>::iterator it;

        // Mark index node as states
        this->_states[state] = 1;
        path.push(state);

        while (!path.empty()) {
            // Dequeue curr_state top vertex
            curr_state = path.front();
            path.pop();

            // Analyze all possible moves as new potential states
            for (int op = 0; op < NOPERATORS; op++) {
                switch (rnum) {
                    case EMPTYA :
                        if (curr_state.first == 0) {
                            bad_move = true;
                        }
                        break;
                        
                    case EMPTYB :
                        if (curr_state.second == 0) {
                            bad_move = true;
                        }
                        break;
         
                    case FILLA :
                        if (curr_state.first == cap_jug_a) {
                            bad_move = true;
                        }
                        break;
         
                    case FILLB :
                        if (curr_state.second == cap_jug_b) {
                            bad_move = true;
                        }
                        break;
         
                    case POURAB :
                        if (((cap_jug_b - curr_state.second) == 0) || (curr_state.first == 0)) {
                            bad_move = true;
                        }

                        fill_amount_b = cap_jug_b - curr_state.second;

                        if (curr_state.first <= fill_amount_b) {
                            fill = curr_state.first;
                        } else {
                            fill = fill_amount_b;
                        }

                        break;
         
                    case POURBA :
                        if (((cap_jug_a - curr_state.first) == 0) || (curr_state.second == 0)) {
                            bad_move = true;
                        }

                        fill_amount_a = cap_jug_a - curr_state.first;

                        if (curr_state.second <= fill_amount_a) {
                            fill = curr_state.second;
                        } else {
                            fill = fill_amount_a;
                        }

                        break;

                    default:
                        break;
                }
            }

            for (it = this->_states.begin(); it != this->_states.end(); ++it) {
                if (it->second == false) {
                    it->second = true;
                    path.push(it->first);
                }
            }            
        }
        
    };
     

private:
    int _num_vertices;
    //list<pair<int, int> >* _adj_pair; 
    map<pair<int, int>, bool> _states;
};

void strategyB(string file_name, pair<int, int> curr_state, int goal_jug_a, 
    int goal_jug_b, int cap_jug_a, int cap_jug_b) {
    // Create state space
    int size  = (cap_jug_a + 1) * (cap_jug_b + 1);
    map<pair<int, int>, bool> states;

    // Iniitalize map and list everything as unstates
    for (int i = 0; i < (cap_jug_a + 1); i++) {
        for (int j = 0; j < (cap_jug_b + 1); j++) {
            states.insert(pair<pair<int, int>, bool>({i, j}, false));
        }
    }

    // Create StateSpace object
    SearchSpace ss(size, states); 

    // TODO: Refactor this to setup edges properly per water jug problem
    /*for (int i = 0; i < (cap_jug_a + 1); i++) {
        for (int j = 0; j < (cap_jug_b + 1); j++) {
            ss.addEdge(count, make_pair(i, j)); 
            count++;
        }
    }*/

    // Append to the output file
    ofstream out_file;
    out_file.open(file_name, ofstream::out | ofstream::app);

    cout << ">Strategy B" << endl;
    cout << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << curr_state.first << "," << curr_state.second << ")" << endl;
    out_file << ">Strategy B\n";
    out_file << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << curr_state.first << "," << curr_state.second << ")\n";
    
    ss.bfs(curr_state);
    out_file.close();
} 
