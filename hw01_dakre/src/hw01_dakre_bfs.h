#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <queue>

using namespace std;

void strategyB(string file_name, pair<int, int> curr_state, queue<pair<int, int> >, 
    int goal_jug_a, int goal_jug_b, int cap_jug_a, int cap_jug_b) {
    // Forward declarations

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
