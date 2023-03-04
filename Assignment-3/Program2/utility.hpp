#include <iostream>
#include <fstream>
#include <vector>
#include "math.h"

#ifndef utility_h
#define utility_h

#define DEFAULT_FILE "titanic_project.csv"

using namespace std;

// Used to open the file of the project
ifstream openFile(int argc, char** argv) {

    ifstream fs;
    
    if (argc == 1) {
        cout << "Attempting to open default file titanic_project.csv" << endl << endl;
        fs.open(DEFAULT_FILE);
    }

    else {
        cout << "Opening file name " << argv[1] << endl << endl;
        fs.open(argv[1]);
    }

    return fs;
}

// Prints a given 2D matrix as given
void printMatrix(vector<vector<double>> matrix) {

    cout << "[";
    for (int i = 0; i < matrix.size(); i++) {
        cout << "[";
        for (int j = 0; j < matrix.at(0).size(); j++) {
            cout << matrix[i][j] << ",";
        }
        cout << "]," << endl;
    }
    cout << "]" << endl;
}

// Prints a given 1D matrix as given
void printMatrix(vector<double> matrix) {

    cout << "[";
    for (int i = 0; i < matrix.size() - 1; i++) {
        cout << matrix[i] << ",";
    }
    cout << matrix[matrix.size() - 1] << "]," << endl;
}

// Multiplies a 2D by a 2D
vector<vector<double>> matrixMultiply(vector<vector<double>> x1, vector<vector<double>> x2) {


    
    // First check the dimensions of the vectors
    if (x1.at(0).size() != x2.size()) {
        cout << "Matrices are not the correct sizes" << endl;
        cout << "Matrix 1 size: " << x1.size() << " x " << x1.at(0).size() << endl;
        cout << "Matrix 2 size: " << x2.size() << " x " << x2.at(0).size() << endl;
        exit(1);
    }
    else if (x1.size() == 0) {
        cout << "Matrix 1 size is 0" << endl;
        exit(1);
    }
    else if (x2.at(0).size() == 0) {
        cout << "Matrix 2 size is 0" << endl;
        exit(1);
    }

    // Makes a new vector of the right size and fills it with 0's
    vector<vector<double>> result(x1.size());
    for (int i = 0; i < x1.size(); i++) {
        vector<double> row (x2.at(0).size());
        result.at(i) = row;
    }

    int numRows = result.size();
    int numCols = result.at(0).size();
    int numMults = x2.size();

    // Does the multiplication
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            for (int k = 0; k < numMults; k++) {
                result[i][j] += x1[i][k] * x2[k][j];
            }
        }
    }

    return result;
}

// Multiplies a 2D by a 1D
vector<vector<double>> matrixMultiply(vector<vector<double>> x1, vector<double> x2) {


    
    // First check the dimensions of the vectors
    if (x1.at(0).size() != x2.size()) {
        cout << "Matrices are not the correct sizes" << endl;
        cout << "Matrix 1 size: " << x1.size() << " x " << x1.at(0).size() << endl;
        cout << "Matrix 2 size: " << x2.size() << " x " << "1" << endl;
        exit(1);
    }
    else if (x1.size() == 0) {
        cout << "Matrix 1 size is 0" << endl;
        exit(1);
    }

    // Makes a new vector of the right size and fills it with 0's
    vector<vector<double>> result(x1.size());
    for (int i = 0; i < x1.size(); i++) {
        vector<double> row (1);
        result.at(i) = row;
    }

    int numRows = result.size();
    int numCols = result.at(0).size();
    int numMults = x2.size();

    // Does the multiplication
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            for (int k = 0; k < numMults; k++) {
                result[i][j] += x1[i][k] * x2[k];
            }
        }
    }

    return result;
}

// Returns the transpose of a matrix
vector<vector<double>> transpose(vector<vector<double>> matrix) {

    vector<vector<double>> transpose (matrix.at(0).size());

    for (int i = 0; i < matrix.at(0).size(); i++) {
        vector<double> row (matrix.size());
        for (int j = 0; j < matrix.size(); j++) {
            row[j] = matrix[j][i];
        }
        transpose[i] = row;
    }

    return transpose;
}

// Gets labels from a single column
vector<vector<double>> getLabels(vector<vector<double>> matrix, int column) {

    vector<vector<double>> labels (matrix.size());

    for (int i = 0; i < matrix.size(); i++) {
        vector<double> row = {matrix[i][column]};
        labels.at(i) = row;
    }

    return labels;
}

// Returns a datamatrix where a variable is binded to a column of a dataframe
// Takes a dataframe, column number, and value to bind
vector<vector<double>> cbind(vector<vector<double>> dataframe, int columnNum, double bindValue) {

    vector<vector<double>> dataMatrix (dataframe.size());

    int size = dataframe.size();
    for (int i = 0; i < size; i++) {
        vector<double> row = {bindValue, dataframe.at(i).at(columnNum)};
        dataMatrix.at(i) = row;
    }

    return dataMatrix;
}

// Function that prints the sum of a vector
double Sum(vector<double> &vector) {

    double sum = 0;

    // Single for loop to sum all values
    for (double i : vector) {
        sum += i;
    }

    return sum;
}

// Finds the sum from the sum function and divides it by number of observations
double Mean(vector<double> &vector, int observations) {

    double sum = Sum(vector);
    double mean = sum / observations;

    return mean;

}

double Variance(vector<double> vec, double mean) {

    vector<double> var (vec.size());

    for (int i = 0; i < vec.size(); i++) {
        var[i] = pow(vec[i] - mean, 2);
    }

    return Sum(var) / var.size();
}

#endif