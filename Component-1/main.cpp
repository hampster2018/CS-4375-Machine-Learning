#include "utility.hpp"
#include "stats.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define MAX_SIZE 1000
#define DEFAULT_FILE "Boston.csv"

using namespace std;
int main(int argc, char** argv) {

    // Takes in the headings and their respective values
    string line;
    string rm_in, medv_in;

    // Stores all doubles up to MAX_SIZE
    vector<double> rm(MAX_SIZE);
    vector<double> medv(MAX_SIZE);

    // Utility function to open a file different from Boston.csv if needed
    ifstream fs = openFile(argc, argv);

    // Grabs the headings and prints
    cout << "Reading line 1" << endl;
    getline(fs, line);
    cout << "Headings: " << line << endl;

    // Main for loop that stores 7each line of csv file in the vectors
    // TODO - change this to support csv files of any number of headers
    int observations = 0;
    while (fs.good()) {

        // Gets 2 double values and stores them in strings
        getline(fs, rm_in, ',');
        getline(fs, medv_in, '\n');

        // Converts string to double and stores it in vector
        rm.at(observations) = stof(rm_in);
        medv.at(observations) = stof(medv_in);

        observations++;
    }

    // Resize the vector to get rid of extra empty values print new length
    rm.resize(observations);
    medv.resize(observations);
    cout << "There are " << observations << " observations in the file" << endl;

    // Close the csv file
    fs.close();

    // Print the stats for both values
    cout << "\nStats for rm" << endl;
    print_stats(rm, observations);

    cout << "\nStats for medv" << endl;
    print_stats(medv, observations);

    cout << "\nCovariance = " << covar(rm, medv, observations) << endl;

    cout << "\nCorrelation = " << cor(rm, medv, observations) << endl;

    cout << endl << "Program Terminated";
    return 0;
}