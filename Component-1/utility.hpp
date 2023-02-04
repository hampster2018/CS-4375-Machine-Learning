#include <iostream>
#include <fstream>

#ifndef utility_h
#define utility_h

using namespace std;

ifstream openFile(int argc, char** argv) {

    ifstream fs;
    
    if (argc == 1) {
        cout << "Attempting to open default file Boston.csv" << endl;
        fs.open("Boston.csv");
    }

    else {
        cout << "Opening file name " << argv[1] << endl;
        fs.open(argv[1]);
    }

    return fs;
}

#endif