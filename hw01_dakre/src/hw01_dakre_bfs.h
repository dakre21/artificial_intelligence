#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <queue>
#include <list>

using namespace std;

class SearchSpace {
public:
    SearchSpace(int num_vertices) {
        this->_num_vertices = num_vertices;
        this->_adj_pair = new list<pair<int, int> >[num_vertices];
    };

    ~SearchSpace() { 
        // Do nothing
    };

    void addEdge(int index, pair<int, int> state) {
        this->_adj_pair[index].push_back(state);
    };

    void bfs(int index) {
        // Perform BFS at index
    };
     

private:
    int _num_vertices;
    list<pair<int, int> >* _adj_pair; 
};

void strategyB(string file_name, pair<int, int> curr_state, queue<pair<int, int> >, 
    int goal_jug_a, int goal_jug_b, int cap_jug_a, int cap_jug_b) {
    // Create state space
    int count = 0;
    int size = (cap_jug_a + 1) * (cap_jug_b + 1);
    SearchSpace ss(size); 

    for (int i = 0; i < (cap_jug_a + 1); i++) {
        for (int j = 0; j < (cap_jug_b + 1); j++) {
            ss.addEdge(count, {i, j}); 
            count++;
        }
    }

    // Append to the output file
    ofstream out_file;
    out_file.open(file_name, ofstream::out | ofstream::app);

    cout << ">Strategy B" << endl;
    cout << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << curr_state.first << "," << curr_state.second << ")" << endl;
    out_file << ">Strategy B\n";
    out_file << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << curr_state.first << "," << curr_state.second << ")\n";
 
    out_file.close();
} 
