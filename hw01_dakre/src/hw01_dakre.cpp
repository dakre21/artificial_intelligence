#include "hw01_dakre.h"

int main(int argc, const char * argv[]) {
    // Forward declarations for algorithm
    const char* file_name = "output.txt";
    string str            = "";

    // Step 0 - Readin the input file
    ifstream file_in;
    file_in.open(argv[1]);

    // Check if file exists
    if (!file_in) {
        cerr << "ERROR: Unable to open file " << argv[1] << endl;
        exit(1);
    }
   
    // Step 1 - Split input file into container capacity, initial state, and goal state
    while (file_in >> str) {
        cout << str << endl; 
    }

    // Step 2 - Apply strategy A (random) to get to goal state 

    // Step 3 - Apply strategy B (systematic state expansion) to get to goal state

    cout << "Strategy A" << endl;
    cout << ">Starting out with a 4-gal jug and a 3-gal jug ---state:(4,0)" << endl;
    cout << ">Emptythe4-galjug---state:(0,0)" << endl;
    cout << endl;
    cout << ">Strategy B" << endl;
    cout << ">Starting out with a 4-gal jug and a 3-gal jug ---state:(4,0)" << endl;
    cout << ">Pourwaterfromthe4-galjugintothe3-galjug---state:(1, 3)" << endl;

    ofstream out_file;
    out_file.open(file_name);
    out_file << "Strategy A\n";
    out_file << ">Starting out with a 4-gal jug and a 3-gal jug ---state:(4,0)\n";
    out_file << ">Emptythe4-galjug---state:(0,0)\n";
    out_file << "\n";
    out_file << ">Strategy B\n";
    out_file << ">Starting out with a 4-gal jug and a 3-gal jug ---state:(4,0)\n";
    out_file << ">Pourwaterfromthe4-galjugintothe3-galjug---state:(1, 3)\n";
    out_file.close();

    return 0;
}
