#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <vector>
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
        this->_states = states; 
    };

    ~SearchSpace() { 
        // Do nothing
    };

    void bfs(pair<int, int> state, int cap_jug_a, int cap_jug_b, int goal_jug_a, int goal_jug_b, string file_name) {
        // Forward declarations
        int fill_amount_a         = 0;
        int fill_amount_b         = 0;
        int fill                  = 0;
        bool found_op             = true;
        pair<int, int> curr_state = state;
        vector<pair<int, int> > path;
        map<pair<int, int>, int> pot_states;
        map<pair<int, int>, bool>::iterator sub_it;
        map<pair<int, int>, int>::iterator it;

        // Mark index node as states
        this->_states[state] = 1;
        path.insert(path.begin(), state);

        // Append to the output file
        ofstream out_file;
        out_file.open(file_name, ofstream::out | ofstream::app);

        cout << endl;
        out_file << "\n";
        cout << ">Strategy B" << endl;
        cout << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
            "-gal jug --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
        out_file << ">Strategy B\n";
        out_file << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
            "-gal jug --- state: (" << curr_state.first << "," << curr_state.second << ")\n";

        while (!path.empty()) {
            for (size_t i = 0; i < path.size(); i++) {
                curr_state = path[i];
                for (it = pot_states.begin(); it != pot_states.end(); ++it) {
                    if (curr_state == it->first) {
                        switch (it->second) {
                            case EMPTYA :
                                cout << ">Empty the " << cap_jug_a << "-gal jug";
                                out_file << ">Empty the " << cap_jug_a << "-gal jug";
                                cout << " --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
                                out_file << " --- state: (" << curr_state.first << "," << curr_state.second << ")\n";
                                found_op = true;
                                break;

                            case EMPTYB :
                                cout << ">Empty the " << cap_jug_b << "-gal jug";
                                out_file << ">Empty the " << cap_jug_b << "-gal jug";
                                cout << " --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
                                out_file << " --- state: (" << curr_state.first << "," << curr_state.second << ")\n";
                                found_op = true;
                                break;

                            case FILLA :
                                cout << ">Fill the " << cap_jug_a << "-gal jug";
                                out_file << ">Fill the " << cap_jug_a << "-gal jug";
                                cout << " --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
                                out_file << " --- state: (" << curr_state.first << "," << curr_state.second << ")\n";
                                found_op = true;
                                break;
           
                            case FILLB :
                                cout << ">Fill the " << cap_jug_b << "-gal jug";
                                out_file << ">Fill the " << cap_jug_b << "-gal jug";
                                cout << " --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
                                out_file << " --- state: (" << curr_state.first << "," << curr_state.second << ")\n";
                                found_op = true;
                                break;

                            case POURAB :
                                cout << ">Pour water from the " << cap_jug_a << "-gal jug into the " 
                                    << cap_jug_b << "-gal jug";
                                out_file << ">Pour water from the " << cap_jug_a << "-gal jug into the " 
                                    << cap_jug_b << "-gal jug";
                                cout << " --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
                                out_file << " --- state: (" << curr_state.first << "," << curr_state.second << ")\n";
                                found_op = true;
                                break;

                            case POURBA :
                                cout << ">Pour water from the " << cap_jug_b << "-gal jug into the " 
                                    << cap_jug_a << "-gal jug";
                                out_file << ">Pour water from the " << cap_jug_b << "-gal jug into the " 
                                    << cap_jug_a << "-gal jug";
                                cout << " --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
                                out_file << " --- state: (" << curr_state.first << "," << curr_state.second << ")\n";
                                found_op = true;
                                break;
             
                            default:
                                break;
                        }
                        break;
                    }

                    
                }
                if (found_op) {
                    path.erase(path.begin() + i);
                    found_op = false;
                    break;
                }
            }
            
            // Check if goal state is reached
            if ((curr_state.first == goal_jug_a && curr_state.second == goal_jug_b) ||
                (goal_jug_a == -1 && curr_state.first <= cap_jug_a && 
                curr_state.second == goal_jug_b) ||
                (goal_jug_b == -1 && curr_state.second <= cap_jug_b &&
                curr_state.first == goal_jug_a) ||
                (goal_jug_a == -1 && goal_jug_b == -1)) {
                break;
            }

            // Reset potential states
            pot_states.clear();

            // Analyze all possible moves as new potential states
            for (int op = 0; op < NOPERATORS; op++) {
                switch (op) {
                    case EMPTYA :
                        if (curr_state.first > 0) {
                            pot_states.insert(pair<pair<int, int>, int>({0, curr_state.second}, EMPTYA));  
                        }
                        break;
                        
                    case EMPTYB :
                        if (curr_state.second > 0) {
                            pot_states.insert(pair<pair<int, int>, int>({curr_state.first, 0}, EMPTYB));  
                        }
                        break;
         
                    case FILLA :
                        if (curr_state.first < cap_jug_a) {
                            pot_states.insert(pair<pair<int, int>, int>({cap_jug_a, curr_state.second}, FILLA));  
                        }
                        break;
         
                    case FILLB :
                        if (curr_state.second < cap_jug_b) {
                            pot_states.insert(pair<pair<int, int>, int>({curr_state.first, cap_jug_b}, FILLB));  
                        }
                        break;
         
                    case POURAB :
                        if (((cap_jug_b - curr_state.second) == 0) || (curr_state.first == 0)) {
                            break;
                        }

                        fill_amount_b = cap_jug_b - curr_state.second;

                        if (curr_state.first <= fill_amount_b) {
                            fill = curr_state.first;
                        } else {
                            fill = fill_amount_b;
                        }

                        pot_states.insert(pair<pair<int, int>, int>({curr_state.first - fill, curr_state.second + fill}, POURAB));

                        break;
         
                    case POURBA :
                        if (((cap_jug_a - curr_state.first) == 0) || (curr_state.second == 0)) {
                            break;
                        }

                        fill_amount_a = cap_jug_a - curr_state.first;

                        if (curr_state.second <= fill_amount_a) {
                            fill = curr_state.second;
                        } else {
                            fill = fill_amount_a;
                        }

                        pot_states.insert(pair<pair<int, int>, int>({curr_state.first + fill, curr_state.second - fill}, POURBA));

                        break;

                    default:
                        break;
                }
            }

            for (it = pot_states.begin(); it != pot_states.end(); ++it) {
                for (sub_it = this->_states.begin(); sub_it != this->_states.end(); ++sub_it) {
                    if (it->first == sub_it->first) {
                        if (sub_it->second == false) {
                            sub_it->second = true;
                            path.insert(path.begin(), sub_it->first);
                        }
                        break;
                    }
                }
            }            
        }

        out_file.close();
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

    // Create StateSpace object and invoke bfs algorithm
    SearchSpace ss(size, states); 
    ss.bfs(curr_state, cap_jug_a, cap_jug_b, goal_jug_a, goal_jug_b, file_name);
} 
