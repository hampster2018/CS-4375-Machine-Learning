#include "utility.hpp"
#include "stats.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "time.h"

#define MAX_SIZE 10000
#define NUMBER_HEADERS 5

// All functions for are defined insides the stats.hpp file to ensure clean code

using namespace std;

int main(int argc, char** argv) {

    // Start Time for whole program
    time_t start = time(NULL);

    // Takes in the headings and their respective values
    string line, input;

    // Stores all doubles up to MAX_SIZE
    vector<vector<double>> dataframe(MAX_SIZE);

    // Utility function to open a file different from Boston.csv if needed
    ifstream fs = openFile(argc, argv);

    // Grabs the headings and prints
    getline(fs, line);
    cout << "Headings: " << line << endl << endl;

    // Main for loop that stores each line of csv file in the vectors
    int observations = 0;
    while (fs.good()) {

        for(int i = -1; i < NUMBER_HEADERS - 1; i++) {
            
            // Removes the first column with the passengers ID
            // Done because we don't need to know a passengers ID
            if (i == -1) {
                getline(fs, input, ',');

                // Makes a vector for each observation to be stored in
                vector<double> row(4);
                dataframe.at(observations) = row;
            }

            // Grabs the final column before the next row
            else if (i == NUMBER_HEADERS - 2) {
                getline(fs, input, '\n');
                dataframe.at(observations).at(i) = stof(input);
            }

            // Grabs all columns not equal to the number of headings
            else {
                getline(fs, input, ',');
                dataframe.at(observations).at(i) = stof(input);
            }
            
        }

        // Moves to the next observation
        observations++;
    }

    // Resizes the complete dataframe to the correct size
    dataframe.resize(observations);

    // Splits into Train/Test split by returning a list of two pointers to 2 2D vectors of the correct size
    auto [train, test] = splitDataframe(dataframe, 800);

    // Setup Basic Variables
    vector<vector<double>> dataMatrix = cbind(train, 2, 1);
    vector<vector<double>> labels = getLabels(train, 1);

    // Prediction variables
    vector<vector<double>> test_matrix = cbind(test, 2, 1);
    vector<vector<double>> test_labels = getLabels(test, 1);

    // Naive Bayes

    // Calculate the current probability of someone surviving
    auto [aprior, countSurvived] = apriors(getLabels(train, 1));

    // Find Qualitative Likelihoods

    vector<vector<double>> lhClass = likelihood(train, countSurvived, 0, 3, 1);
    vector<vector<double>> lhSex = likelihood(train, countSurvived, 2, 2, 0);

    // Outputs class chances
    cout << "The Likelihood values for p(pclass | survived)" << endl;
    printMatrix(lhClass);
    cout << endl;

    // Outputs sex chances
    cout << "The Likelihood values for p(sex | survived)" << endl;
    printMatrix(lhSex);
    cout << endl;

    // Find the mean and variance of Age 
    auto [meanAge, varianceAge] = meanVariance(train);

    // Predicts and prints stats
    vector<vector<double>> prediction1 = predictNaive(test, aprior, lhClass, lhSex, meanAge, varianceAge);
    printStats(prediction1, test_labels, 2);

    // End Time for Training
    time_t end = time(NULL);
    cout << "Time taken for whole program: " << end - start << endl;

    return 0;
}