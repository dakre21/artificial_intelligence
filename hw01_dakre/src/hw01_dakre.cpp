#include "hw01_dakre.h"

int main(int argc, const char * argv[]) {
    // Forward declarations for algorithm
    const char* file_name = "output.txt";
    string str            = "";
    int cap_jug_a         = 0;
    int cap_jug_b         = 0;
    int init_jug_a        = 0;
    int init_jug_b        = 0;
    int goal_jug_a        = 0;
    int goal_jug_b        = 0;
    int count             = 0;
    pair<int, int> curr_state;
    const char* tmp;

    // Step 0 - Readin the input file
    ifstream file_in;
    file_in.open(argv[1]);

    // Seed random number generator
    srand(time(NULL));

    // Check if file exists
    if (!file_in) {
        cerr << "ERROR: Unable to open file " << argv[1] << endl;
        exit(1);
    }
   
    // Step 1 - Split input file into container capacity, initial state, and goal state
    while (getline(file_in, str)) {
        tmp = strstr(str.c_str(), ":");

        // Input file layout assumption:
        // Capacity of jug A 
        // Capacity of jug B
        // Initial State
        // Goal State 
        switch (count) {        
            case 0 : sscanf(tmp, ": %d", &cap_jug_a); break;
            case 1 : sscanf(tmp, ": %d", &cap_jug_b); break;
            case 2 : sscanf(tmp, ": %d %d", &init_jug_a, &init_jug_b); break;
            case 3 : sscanf(tmp, ": %d %d", &goal_jug_a, &goal_jug_b); break;
            default:
                break;
        }

        count++;
    }

    // Set current state of jugs to initial state
    curr_state = {init_jug_a, init_jug_b};

    // Step 2- Apply strategy A (random) to get to goal state
    strategyA(file_name, curr_state, goal_jug_a, goal_jug_b, cap_jug_a, cap_jug_b);

    // Step 3 - Apply strategy B (BFS) to get to goal state 
    strategyB(file_name, curr_state, goal_jug_a, goal_jug_b, cap_jug_a, cap_jug_b);
 
    return 0;
}
