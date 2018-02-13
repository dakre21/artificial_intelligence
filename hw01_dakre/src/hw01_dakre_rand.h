#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>

// Definitions for limits and states
#define LIMIT   250
#define NSTATES 6
#define EMPTYA  0
#define EMPTYB  1 
#define FILLA   2
#define FILLB   3
#define POURAB  4
#define POURBA  5

using namespace std;

void strategyA(string file_name, pair<int, int> curr_state, int goal_jug_a, int goal_jug_b, 
    int cap_jug_a, int cap_jug_b) {
    // Forward declaration of stack variables
    bool solved           = false;
    bool bad_move         = false;
    int fill_amount_a     = 0;
    int fill_amount_b     = 0;
    int fill              = 0;
    int rnum              = 0;
    int count             = 0;

    // Setup output file
    ofstream out_file;
    out_file.open(file_name);

    cout << ">Strategy A" << endl;
    cout << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << curr_state.first << "," << curr_state.second << ")" << endl;
    out_file << ">Strategy A\n";
    out_file << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << curr_state.first << "," << curr_state.second << ")\n";
    while (!solved) {
        // Check if count has exceeded limit
        if (count >= LIMIT) {
            break;
        }

        // Check if goal state is reached
        if ((curr_state.first == goal_jug_a && curr_state.second == goal_jug_b) ||
            (goal_jug_a == -1 && curr_state.first <= cap_jug_a && 
             curr_state.second == goal_jug_b) ||
            (goal_jug_b == -1 && curr_state.second <= cap_jug_b &&
             curr_state.first == goal_jug_a) ||
            (goal_jug_a == -1 && goal_jug_b == -1)) {
            solved = true;
            break;
        }

        // Randomly select a state per strategy A
        rnum = rand() % NSTATES;
        switch (rnum) {
            case EMPTYA :
                if (curr_state.first == 0) {
                    bad_move = true;
                    break;
                }
                curr_state.first = 0;            
                cout << ">Empty the " << cap_jug_a << "-gal jug";
                out_file << ">Empty the " << cap_jug_a << "-gal jug";
                break;
                
            case EMPTYB :
                if (curr_state.second == 0) {
                    bad_move = true;
                    break;
                }
                curr_state.second = 0;            
                cout << ">Empty the " << cap_jug_b << "-gal jug";
                out_file << ">Empty the " << cap_jug_b << "-gal jug";
                break;
 
            case FILLA :
                if (curr_state.first == cap_jug_a) {
                    bad_move = true;
                    break;
                }
                curr_state.first = cap_jug_a;            
                cout << ">Fill the " << cap_jug_a << "-gal jug";
                out_file << ">Fill the " << cap_jug_a << "-gal jug";
                break;
 
            case FILLB :
                if (curr_state.second == cap_jug_b) {
                    bad_move = true;
                    break;
                }
                curr_state.second = cap_jug_b;            
                cout << ">Fill the " << cap_jug_b << "-gal jug";
                out_file << ">Fill the " << cap_jug_b << "-gal jug";
                break;
 
            case POURAB :
                if (((cap_jug_b - curr_state.second) == 0) || (curr_state.first == 0)) {
                    bad_move = true;
                    break;
                }

                fill_amount_b = cap_jug_b - curr_state.second;

                if (curr_state.first <= fill_amount_b) {
                    fill = curr_state.first;
                } else {
                    fill = fill_amount_b;
                }

                curr_state.first -= fill;
                curr_state.second += fill;

                cout << ">Pour water from the " << cap_jug_a << "-gal jug into the " 
                    << cap_jug_b << "-gal jug";
                out_file << ">Pour water from the " << cap_jug_a << "-gal jug into the " 
                    << cap_jug_b << "-gal jug";
                break;
 
            case POURBA :
                if (((cap_jug_a - curr_state.first) == 0) || (curr_state.second == 0)) {
                    bad_move = true;
                    break;
                }

                fill_amount_a = cap_jug_a - curr_state.first;

                if (curr_state.second <= fill_amount_a) {
                    fill = curr_state.second;
                } else {
                    fill = fill_amount_a;
                }

                curr_state.first += fill;
                curr_state.second -= fill;

                cout << ">Pour water from the " << cap_jug_b << "-gal jug into the " 
                    << cap_jug_a << "-gal jug";
                out_file << ">Pour water from the " << cap_jug_b << "-gal jug into the " 
                    << cap_jug_a << "-gal jug";
                break;

            default:
                break;
        }

        if (!bad_move) {
            cout << " --- state: (" << curr_state.first << "," << curr_state.second << ")" << endl;
            out_file << " --- state: (" << curr_state.first << "," << curr_state.second << ")\n";
        } else {
            bad_move = false;
            continue;
        }

        count++;
    }

    out_file.close();
}
