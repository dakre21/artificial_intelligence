#include "hw03_dakre.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>

// Define Possible Actions
#define ADJ_MOVE_L  0
#define ADJ_MOVE_R  1
#define HOP_ONE_L   2
#define HOP_ONE_R   3
#define HOP_TWO_L   4
#define HOP_TWO_R   5
#define NUM_ACTIONS 6

// Globals
array<int, SIZE> init_state = { 
    BLACK, 
    BLACK, 
    BLACK, 
    WHITE, 
    WHITE, 
    WHITE, 
    EMPTY 
};

vector<Node> observed;

int main(int argc, const char* argv[]) {
    // Forward declarations
    int   hn               = 3;
    int   total_cost       = 0;
    int   states_expanded  = 0;
    int   empty_pos        = 0;
    int   temp_hn          = 0;
    int   temp_cost        = 0;
    int   match            = 0;
    int   index            = 0;
    bool  finished         = false;
    bool  skip             = false;
    array<int, SIZE> curr_state;
    array<int, SIZE> temp_state;

    // Start A* process
    // Step 1 - Populate Initial Node
    Node node = Node(init_state, hn, 0);
    node.setVisited();

    for (size_t i = 0; i < SIZE; i++) {
        cout << to_string(init_state[i]);
    }
    cout << endl;

    for (size_t i = 0; i < SIZE; i++) {
        cout << to_string(node.getState()[i]);
    }
    cout << endl;

    // Step 2 - Push initial node into observed structures
    observed.push_back(node);

    // Log Initial state
    cout << "BBBWWWE : G(n) = 0 : h(n) = " << to_string(hn) << endl;

    int count = 0;

    // Step 3 - Loop until solution found
    while (finished != true) {
        // Step 4 - Grab current node and state
        curr_state = observed[index].getState();

        cout << "Current state" << endl;
        for (size_t i = 0; i < SIZE; i++) {
          cout << curr_state[i];
        }
        cout << endl;

        if (count > 5) {
            return 0;
        }

        cout << "*********************BIG LOOP ITERATION************* " << to_string(count) << endl;

        for (size_t i = 0; i < SIZE; i++) {
            if (curr_state[i] == EMPTY) {
                empty_pos = i;
                cout << "Empty pos " << to_string(empty_pos) << endl;
            }
        }

        // Step 5 - Expand state by applying actions
        // Step 6 - Take action w/ smallest cost w/ underestimate hn
        for (size_t action = 0; action < NUM_ACTIONS; action++) {
            // Re-initialize inner loop values
            temp_cost  = 0;
            temp_hn    = 0;
            skip       = false;
            temp_state = curr_state;

            // Switch on the action
            switch (action) {
                case ADJ_MOVE_L:
                    cout << "ADJ L MOVE" << endl;
                    if (empty_pos < (SIZE - 1)) {
                        temp_state[empty_pos+1] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos+1];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }
                    break;
                
                case ADJ_MOVE_R:
                    cout << "ADJ R MOVE" << endl;
                    if (empty_pos > 0) {
                        temp_state[empty_pos-1] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos-1];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_ONE_L:
                    cout << "HOP ONE L" << endl;
                    if (empty_pos < (SIZE - 2)) {
                        temp_state[empty_pos+2] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos+2];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_ONE_R:
                    cout << "HOP ONE R" << endl;
                    if (empty_pos > 1) {
                        temp_state[empty_pos-2] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos-2];
                        temp_cost += 1;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_TWO_L:
                    cout << "HOP TWO L" << endl;
                    if (empty_pos < (SIZE - 3)) {
                        temp_state[empty_pos+3] = curr_state[empty_pos];
                        temp_state[empty_pos] = curr_state[empty_pos+3];
                        temp_cost += 2;
                    } else {
                        skip = true;
                    }

                    break;

                case HOP_TWO_R:
                    cout << "HOP TWO R" << endl;
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

            cout << "Temporary state" << endl;
            for (size_t i = 0; i < SIZE; i++) {
              cout << temp_state[i];
            }
            cout << endl;

            for (size_t i = 0; i < observed.size(); i++) {
                match = 0;
                for (size_t j = 0; j < SIZE; j++) {
                    if (observed[i].getState()[j] == temp_state[j]) {
                        match += 1;
                    }
                }

                if (match == SIZE) {
                    // Do not push duplicates into list unless cost is less
                    // then remove pre-existing node
                    if (observed[i].getHn() < temp_hn) {
                        skip = false; 
                    } else {
                        skip = true;
                    }
                    break;
                }
            }

            if (skip != true) {
                observed.push_back(Node(temp_state, temp_hn, (temp_cost + total_cost)));
                states_expanded += 1;
            }
        }

        // Step 7 - Mark least costing path as visited
        temp_cost = 0;
        for (size_t i = 0; i < observed.size(); i++) {
            cout << "Iteration " << to_string(i) << endl;
            cout << "Obs cost " << to_string(observed[i].getCost()) << endl;
            cout << "Obs hn " << to_string(observed[i].getHn()) << endl;
            cout << "Obs visited " << to_string(observed[i].getVisited()) << endl;
            cout << "Obs state " << endl;
            for (size_t j = 0; j < SIZE; j++) {
                cout << observed[i].getState()[j];
            }
            cout << endl;

            if (observed[i].getVisited() != true) {
                if (temp_cost == 0) {
                    cout << "In here 1" << endl;
                    index = i;
                    temp_cost = observed[i].getCost();
                    temp_hn = observed[i].getHn();
                    cout << "Temp cost " << to_string(temp_cost) << endl;
                } else if ((temp_cost + temp_hn) > 
                    (observed[i].getCost() + observed[i].getHn())) {
                    cout << "In here 2" << endl;
                    index = i;
                    temp_cost = observed[i].getCost();
                    temp_hn = observed[i].getHn();
                    cout << "Temp cost " << to_string(temp_cost) << endl;
                }
            }
        }

        observed[index].setVisited();

        // Step 8 - Collect the current total cost
        total_cost += observed[index].getCost();

        // Log New State
        for (int i = 0; i < SIZE; i++) {
            if (observed[index].getState()[i] == WHITE) {
                cout << "W";
            } else if (observed[index].getState()[i] == BLACK) {
                cout << "B";
            } else {
                cout << "E";
            }
        }

        cout << " : G(n) = " << to_string(total_cost) << " : h(n) = " 
          << to_string(observed[index].getHn()) << endl;

        // Step 9 - Check if state is equal to goal state
        if (observed[index].getHn() == 0) {
            finished = true;
        }

        count++;
    }

    // Log total states and cost
    cout << "Total cost = " << to_string(total_cost) << endl;
    cout << "Number of states expanded = " << to_string(states_expanded) << endl;
}
