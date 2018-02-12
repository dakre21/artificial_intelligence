#include "hw01_dakre.h"

// States and Limits
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
    int curr_jug_a        = 0;
    int curr_jug_b        = 0;
    int count             = 0;
    int rnum              = 0;
    int pour_jug          = 0;
    bool bad_move         = false;
    bool solved           = false;
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
        //cout << str << endl;
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
    curr_jug_a = init_jug_a;
    curr_jug_b = init_jug_b;

    // Step 2 - Apply strategy A (random) to get to goal state 
    cout << ">Strategy A" << endl;
    cout << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug ---state:(" << init_jug_a << "," << init_jug_b << ")" << endl;
    out_file << ">Strategy A\n";
    out_file << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug ---state:(" << init_jug_a << "," << init_jug_b << ")\n";
    while (!solved) {
        // Check if count has exceeded limit
        if (count >= LIMIT) {
            break;
        }

        // Randomly select a state per strategy A
        rnum = rand() % NSTATES;
        switch (rnum) {
            case EMPTYA :
                // If jug is already full negate this move
                if (curr_jug_a == 0) {
                    bad_move = true;
                    break;
                }
                curr_jug_a = 0;            
                cout << "Empty the " << cap_jug_a << "-gal jug";
                out_file << "Empty the " << cap_jug_a << "-gal jug";
                break;
                
            case EMPTYB :
                // If jug is already full negate this move
                if (curr_jug_b == 0) {
                    bad_move = true;
                    break;
                }
                curr_jug_b = 0;            
                cout << "Empty the " << cap_jug_b << "-gal jug";
                out_file << "Empty the " << cap_jug_b << "-gal jug";
                break;
 
            case FILLA :
                // If jug is already full negate this move
                if (curr_jug_a == cap_jug_a) {
                    bad_move = true;
                    break;
                }
                curr_jug_a = cap_jug_a;            
                cout << "Fill the " << cap_jug_a << "-gal jug";
                out_file << "Fill the " << cap_jug_a << "-gal jug";
                break;
 
            case FILLB :
                // If jug is already full negate this move
                if (curr_jug_b == cap_jug_b) {
                    bad_move = true;
                    break;
                }
                curr_jug_b = cap_jug_b;            
                cout << "Fill the " << cap_jug_b << "-gal jug";
                out_file << "Fill the " << cap_jug_b << "-gal jug";
                break;
 
            case POURAB :
                cout << "In pour a to b" << endl;
                pour_jug = curr_jug_a - cap_jug_b - curr_jug_b;
                cout << "pour " << pour_jug << " a " << curr_jug_a << " b " << curr_jug_b << " cap b " << cap_jug_b << endl;

                if (pour_jug <= 0) {
                    bad_move = true;
                    break;
                }                

                curr_jug_a -= pour_jug;
                curr_jug_b += pour_jug;

                cout << "Pour water from the " << cap_jug_a << "-gal jug into the " 
                    << cap_jug_b << "-gal jug";
                out_file << "Pour water from the " << cap_jug_a << "-gal jug into the " 
                    << cap_jug_b << "-gal jug";
                break;
 
            case POURBA :
                cout << "In pour b to a" << endl;
                pour_jug = curr_jug_b - cap_jug_a - curr_jug_a;
                cout << "pour " << pour_jug << " a " << curr_jug_a << " b " << curr_jug_b << " cap a " << cap_jug_a << endl;

                if (pour_jug <= 0) {
                    bad_move = true;
                    break;
                }                

                curr_jug_b -= pour_jug;
                curr_jug_a += pour_jug;

                cout << "Pour water from the " << cap_jug_b << "-gal jug into the " 
                    << cap_jug_a << "-gal jug";
                out_file << "Pour water from the " << cap_jug_b << "-gal jug into the " 
                    << cap_jug_a << "-gal jug";
                break;

            default:
                break;
        }

        if (!bad_move) {
            cout << "  --- state: (" << curr_jug_a << "," << curr_jug_b << ")" << endl;
            out_file << "  --- state: (" << curr_jug_a << "," << curr_jug_b << ")\n";
        } else {
            bad_move = false;
            continue;
        }

        if (curr_jug_a == goal_jug_a && curr_jug_b == goal_jug_b) {
            cout << solved << endl;
            solved = true;
        }

        count++;
    }
  
    /* 
    // Reset solved flag 
    out_file << "\n";
    solved = false; 

    // Set current state of jugs to initial state
    curr_jug_a = init_jug_a;
    curr_jug_b = init_jug_b;

    // Step 3 - Apply strategy B (systematic state expansion) to get to goal state
    cout << ">Strategy B" << endl;
    cout << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug ---state:(" << init_jug_a << "," << init_jug_b << ")" << endl;
    out_file << ">Strategy B\n";
    out_file << ">Starting out with a " << cap_jug_a << "-gal jug and a " << cap_jug_b << 
        "-gal jug ---state:(" << init_jug_a << "," << init_jug_b << ")\n";
    while (!solved) {
        break;
    }
    */

    out_file.close();

    return 0;
}
