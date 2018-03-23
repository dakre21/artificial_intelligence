#include "hw03_dakre.h"

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
    bool  finished        = false;
    int*  curr_state;
    int*  temp_state;
    int   temp_cost;

    // Start A* process
    // Step 1 - Populate Initial Node
    Node node = Node(init_state, hn);

    // Step 2 - Push initial node into visited and observed structures
    visited.push_back(node);
    observed.push_back(node);

    // Step 3 - Loop until solution found
    while (finished != true) {
        // Step 4 - Grab current node and state
        curr_state = visited[states_expanded].get_state();

        // Step 5 - Expand state by applying actions
        // Step 6 - Take action w/ smallest cost w/ underestimate hn
        for (int action = 0; action < NUM_ACTIONS; action++) {
            for (int i = 0; i < SIZE; i++) {
                if (curr_state[i] == EMPTY) {
                    empty_pos = i;
                }
            }

            temp_cost = 0;
            switch (action) {
                case ADJ_MOVE_L:
                    if (empty_pos < SIZE) {
                        
                    }
                    break;
                
                case ADJ_MOVE_R:
                    if (empty_pos > 0) {
                        
                    }
                    break;

                case HOP_ONE_L:
                    if (empty_pos < SIZE - 1) {

                    }
                    break;

                case HOP_ONE_R:
                    if (empty_pos > 1) {

                    }
                    break;

                case HOP_TWO_L:
                    if (empty_pos < SIZE - 2) {

                    }
                    break;

                case HOP_TWO_R:
                    if (empty_pos > 2) {

                    }
                    break;

                default:
                    break;
            }
        }

        // Step 7 - Push state into visited list

        // Step 8 - Check if state is equal to goal state
    }

}
