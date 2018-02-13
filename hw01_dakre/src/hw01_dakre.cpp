#include "hw01_dakre.h"

// Limit
#define LIMIT   250
#define NSTATES 6
#define EMPTYA  0
#define EMPTYB  1 
#define FILLA   2
#define FILLB   3
#define POURAB  4
#define POURBA  5

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
    int rnum              = 0;
    int fill_amount_a     = 0;
    int fill_amount_b     = 0;
    int fill              = 0;
    bool solved           = false;
    bool bad_move         = false;
    queue<pair<int, int> > visited;
    vector<pair<int, int> > states;
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

    // Step 1.2 - Setup state space
    for (int i = 0; i < cap_jug_a; i++) {
        for (int j = 0; j < cap_jug_b; j++) {
            states.push_back(pair<int, int>(i, j));
        }
    }

    // Reset count
    count = 0;

    // Setup output file
    ofstream out_file;
    out_file.open(file_name);

    // Confirm goal states
    if (goal_jug_a < 0) {
        goal_jug_a = cap_jug_a + goal_jug_a;
    }

    if (goal_jug_b < 0) {
        goal_jug_b = cap_jug_b + goal_jug_b;
    }

    // Set current state of jugs to initial state
    visited.push({init_jug_a, init_jug_b});
    curr_state = visited.front();

    // Step 2 - Apply strategy A (random) to get to goal state 
    cout << ">Strategy A" << endl;
    cout << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << init_jug_a << "," << init_jug_b << ")" << endl;
    out_file << ">Strategy A\n";
    out_file << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug --- state:(" << init_jug_a << "," << init_jug_b << ")\n";
    while (!solved) {
        // Check if count has exceeded limit
        if (count >= LIMIT) {
            break;
        }

        if (curr_state.first == goal_jug_a && curr_state.second == goal_jug_b) {
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
    return 0;
}
