#include "hw03_dakre.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>

// Define Possible Actions
#define ADJ_MOVE_L  1
#define ADJ_MOVE_R  2
#define HOP_ONE_L   3
#define HOP_ONE_R   4
#define HOP_TWO_L   5
#define HOP_TWO_R   6
#define NUM_ACTIONS 6

// Globals
int init_state[SIZE] = { 
  BLACK, 
  BLACK, 
  BLACK, 
  WHITE, 
  WHITE, 
  WHITE, 
  EMPTY 
};

vector<Node> visited;
vector<Node> observed;

int main(int argc, const char* argv[]) {
    // Forward declarations
    int   hn              = 3;
    int   total_cost      = 0;
    int   states_expanded = 0;
    int   empty_pos       = 0;
    int   pot_hn          = 0;
    int   temp_hn         = 0;
    int   temp_cost       = 0;
    int   pot_cost        = 0;
    int   match           = 0;
    bool  finished        = false;
    bool  skip            = false;
    int*  curr_state      = NULL;
    int*  temp_state      = NULL;
    int*  pot_state       = NULL;

    // Start A* process
    // Step 1 - Populate Initial Node
    Node node = Node(init_state, hn);

    // Step 2 - Push initial node into visited and observed structures
    visited.push_back(node);
    observed.push_back(node);

    // Log Initial state
    cout << "BBBWWWE : G(n) = 0 : h(n) = " << to_string(hn) << endl;

    // Step 3 - Loop until solution found
    while (finished != true) {
        // Step 4 - Grab current node and state
        curr_state = visited[states_expanded].get_state();
        pot_state  = NULL;
        pot_hn     = 0;
        pot_cost   = 0;

        // Step 5 - Expand state by applying actions
        // Step 6 - Take action w/ smallest cost w/ underestimate hn
        for (size_t action = 0; action < NUM_ACTIONS; action++) {
            for (size_t i = 0; i < SIZE; i++) {
                if (curr_state[i] == EMPTY) {
                    empty_pos = i;
                }
            }

            // Re-initialize inner loop values
            temp_cost  = 0;
            temp_hn    = 0;
            temp_state = curr_state;
            skip       = false;

            // Switch on the action
            switch (action) {
                case ADJ_MOVE_L:
                    if (empty_pos < SIZE) {
                        temp_state[empty_pos+1] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos+1];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }
                    break;
                
                case ADJ_MOVE_R:
                    if (empty_pos > 0) {
                        temp_state[empty_pos-1] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos-1];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_ONE_L:
                    if (empty_pos < SIZE - 1) {
                        temp_state[empty_pos+2] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos+2];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_ONE_R:
                    if (empty_pos > 1) {
                        temp_state[empty_pos-2] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos-2];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_TWO_L:
                    if (empty_pos < SIZE - 2) {
                        temp_state[empty_pos+3] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos+3];
                        temp_cost += 2;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_TWO_R:
                    if (empty_pos > 2) {
                        temp_state[empty_pos-3] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos-3];
                        temp_cost += 2;
                    } else {
                        skip = true;
                    }

                    break;

                default:
                    break;
            }

            if (skip == true) {
                continue;
            }

            for (size_t i = 0; i < SIZE; i++) {
                if (temp_state[i] == BLACK && i < 4) {
                    temp_hn += 1;
                }
            }

            if (pot_state == NULL || (temp_cost + temp_hn) < (pot_cost + pot_hn)) {
                pot_state = temp_state;
                pot_hn    = temp_hn;
                pot_cost  = temp_cost;
            }

            for (size_t i = 0; i < observed.size(); i++) {
                match = 0;
                for (size_t j = 0; j < SIZE; j++) {
                    if (observed[i].get_state()[j] == temp_state[j]) {
                        match += 1;
                    }
                }

                if (match == SIZE) {
                    // Do not push duplicates into list unless cost is less
                    // then remove pre-existing node
                    if (observed[i].get_hn() < temp_hn) {
                        skip = false; 
                    } else {
                        skip = true;
                    }
                    break;
                }
            }

            if (skip != true) {
                observed.push_back(Node(temp_state, temp_hn));
                states_expanded += 1;
            }
        }

        // Step 7 - Push state into visited list
        visited.push_back(Node(pot_state, pot_hn));

        // Step 8 - Collect the current total cost
        total_cost += pot_cost;

        // Log New State
        for (int i = 0; i < SIZE; i++) {
            if (pot_state[i] == WHITE) {
                cout << "W";
            } else if (pot_state[i] == BLACK) {
                cout << "B";
            } else {
                cout << "E";
            }
        }

        cout << " : G(n) = " << to_string(total_cost) << " : h(n) = " 
          << to_string(pot_hn) << endl;

        // Step 9 - Check if state is equal to goal state
        if (pot_hn == 0) {
            finished = true;
        }
    }

    // Log total states and cost
    cout << "Total cost = " << to_string(total_cost) << endl;
    cout << "Number of states expanded = " << to_string(states_expanded) << endl;
}
