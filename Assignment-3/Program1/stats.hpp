#include <iostream>
#include <vector>
#include <tuple>
#include <float.h>
#include <math.h>
#include "utility.hpp"

#ifndef stats_h
#define stats_h

using namespace std;

#define LEARNING_RATE .001

// List of functions used in this project

// Logistic Regression Functions
vector<double> glm (vector<vector<double>> dataMatrix, vector<vector<double>> labels, int numIterations);
vector<vector<double>> predictions(vector<vector<double>> matrix);
double sigmoid(double value);
double accuracy (vector<vector<double>> prediction, vector<vector<double>> labels);
double sensitivity (vector<vector<double>> prediction, vector<vector<double>> labels);
double specificity (vector<vector<double>> prediction, vector<vector<double>> labels);

// Data Manipulation Functions
tuple<vector<vector<double>>, vector<vector<double>>> splitDataframe(vector<vector<double>> dataframe, int numTrain);

// Returns the logistical model weights given a matrix, labels, and the number of training iterations
vector<double> glm (vector<vector<double>> dataMatrix, vector<vector<double>> labels, int numIterations) {

    // Sets initial weights
    vector<double> weights (2);
    weights.at(0) = 1;
    weights.at(1) = 1;

    vector<vector<double>> transposed = transpose(dataMatrix);

    // Does a given number of iterations
    for (int i = 1; i <= numIterations; i++) {

        // Does a matrix multiplication and then completes the sigmoid function to each value
        vector<vector<double>> prob_vector = matrixMultiply(dataMatrix, weights);
        for (int j = 0; j < prob_vector.size(); j++)
            prob_vector[j][0] = sigmoid(prob_vector[j][0]);

        // Makes a vector to compute error
        vector<vector<double>> error (dataMatrix.size());
        for (int j = 0; j < error.size(); j++) {
            vector<double> row = {labels[j][0] - prob_vector[j][0]};
            error[j] = row;
        }


        vector<vector<double>> multiplied = matrixMultiply(transposed, error);
        for (int j = 0; j < weights.size(); j++) {
                weights[j] = weights[j] +  LEARNING_RATE * multiplied[j][0];
        }
    }

    return weights;

}

vector<vector<double>> predictionLogistic(vector<vector<double>> matrix) {

    for (int i = 0; i < matrix.size(); i++) {
        matrix[i][0] = exp(matrix[i][0]) / (1 + exp(matrix[i][0]));
    }

    vector<vector<double>> prediction (matrix.size());

    for (int i = 0; i < matrix.size(); i++) {
        vector<double> row (1);
        prediction[i] = row;
        if (matrix[i][0] > .5)
            prediction[i][0] = 1;
        else
            prediction[i][0] = 0;
    }

    return prediction;
}

// Returns the sigmoid value of a single double by taking a double
double sigmoid(double value) {
    return 1.0 / (1 + exp(-value));
}

// Prints the stats from a given logistical model
void printStats (vector<vector<double>> prediction, vector<vector<double>> labels, int type) {
    
    if (type == 1) {
        cout << "The Logistical Model Stats: " << endl;
    }
    else {
        cout << "The Naive Bayes Model Stats: " << endl;
    }
    cout << "Accuracy: " << accuracy(prediction, labels) << endl;
    cout << "Sensitivity: " << sensitivity(prediction, labels) << endl;
    cout << "Specificity: " << specificity(prediction, labels) << endl << endl; 

}

// Returns accuracy as a double for a given prediction
double accuracy (vector<vector<double>> prediction, vector<vector<double>> labels) {

    double correct = 0;

    for (int i = 0; i < prediction.size(); i++) {
        if (prediction[i][0] == labels[i][0])
            correct += 1;
    }

    return correct / prediction.size();
}

double sensitivity (vector<vector<double>> prediction, vector<vector<double>> labels) {

    double truePositive = 0;
    double falseNegative = 0;

    for (int i = 0; i < prediction.size(); i++) {
        if (prediction[i][0] == 1 && prediction[i][0] == labels[i][0])
            truePositive += 1;
        else if (prediction[i][0] == 0 && prediction[i][0] != labels[i][0])
            falseNegative += 1;
    }

    return truePositive / (truePositive + falseNegative);
}

double specificity (vector<vector<double>> prediction, vector<vector<double>> labels) {

    double trueNegative = 0;
    double falsePositive = 0;

    for (int i = 0; i < prediction.size(); i++) {
        if (prediction[i][0] == 0 && prediction[i][0] == labels[i][0])
            trueNegative += 1;
        else if (prediction[i][0] == 1 && prediction[i][0] != labels[i][0])
            falsePositive += 1;
    }

    return trueNegative / (trueNegative + falsePositive);
}

// Returns a matrix of the current probabilities of survival
tuple<vector<vector<double>>, vector<vector<double>>> apriors(vector<vector<double>> matrix) {
    vector<vector<double>> aprior (2);
    vector<double> row1 (1);
    vector<double> row2 (1);
    aprior[0] = row1;
    aprior[1] = row2;
    vector<vector<double>> countSurvived (2);
    vector<double> row3 (1);
    vector<double> row4 (1);
    countSurvived[0] = row3;
    countSurvived[1] = row4;

    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][0] == 0) {
            countSurvived[0][0] += 1;
            aprior[0][0] += 1;
        }
        else {
            countSurvived[1][0] += 1;
            aprior[1][0] += 1;
        }
    }
    
    aprior[0][0] = aprior[0][0] / matrix.size();
    aprior[1][0] = aprior[1][0] / matrix.size();

    return {aprior, countSurvived};
}

vector<vector<double>> likelihood(vector<vector<double>> matrix, vector<vector<double>> countSurvived, int column, int uniqueVals, int subtract) {

    vector<vector<double>> lh (2);
    for (int i = 0; i < lh.size(); i++) {
        vector<double> row (uniqueVals);
        lh[i] = row;
    }

    for (int i = 0; i < matrix.size(); i++) {
        lh[matrix[i][1]][matrix[i][column] - subtract] += 1;
    }

    for (int i = 0; i < lh.size(); i++) {
        for (int j = 0; j < lh[0].size(); j++) {
            lh[i][j] = lh[i][j] / countSurvived[i][0];
        }
    }

    return lh;

}

tuple<vector<double>, vector<double>> meanVariance(vector<vector<double>> matrix) {

    vector<double> age0 (1000);
    vector<double> age1 (1000);
    int numAge0 = 0;
    int numAge1 = 0;

    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][1] == 0) {
            age0[numAge0] = matrix[i][3];
            numAge0 += 1;
        }
        else {
            age1[numAge1] = matrix[i][3];
            numAge1 += 1;
        }
    }

    age0.resize(numAge0);
    age1.resize(numAge1);

    vector<double> means (2);
    vector<double> variance (2);

    means[0] = Mean(age0, numAge0);
    means[1] = Mean(age1, numAge1);

    variance[0] = Variance(age0, means[0]);
    variance[1] = Variance(age1, means[1]);

    return {means, variance};
}

double calculateQuantitative(double v, double mean_v, double var_v) {

    return ((1 / sqrt(2 * M_PI * var_v)) * exp(-(pow(v - mean_v, 2) / (2 * var_v))));

}

double Naive(vector<vector<double>> aprior, vector<vector<double>> lhClass, vector<vector<double>> lhSex, vector<double> meanAge, vector<double> varianceAge, int classNum, int sex, int age) {


    double num_s = lhClass[1][classNum - 1] * lhSex[1][sex] * aprior[1][0] * calculateQuantitative(age, meanAge[1], varianceAge[1]);
    double num_p = lhClass[0][classNum - 1] * lhSex[0][sex] * aprior[0][0] * calculateQuantitative(age, meanAge[0], varianceAge[0]);
    double denominator = lhClass[1][classNum - 1] * lhSex[1][sex] * calculateQuantitative(age, meanAge[1], varianceAge[1])  * aprior[1][0] + 
                lhClass[0][classNum - 1] * lhSex[0][sex] * calculateQuantitative(age, meanAge[0], varianceAge[0]) * aprior[0][0];

    vector<double> result (2);

    result[0] = num_s / denominator;
    result[1] = num_p / denominator;

    return result[1];

}

vector<vector<double>> predictNaive (vector<vector<double>> matrix, vector<vector<double>> aprior, vector<vector<double>> lhClass, vector<vector<double>> lhSex, vector<double> meanAge, vector<double> varianceAge) {

    vector<vector<double>> prediction (matrix.size());
    for (int i = 0; i < prediction.size(); i++) {
        vector<double> row (1);
        prediction[i] = row;
        double survival = Naive(aprior, lhClass, lhSex, meanAge, varianceAge, matrix[i][0], matrix[i][2], matrix[i][3]);
        if (survival > .5) {
            prediction[i][0] = 0;
        }
        else {
            prediction[i][0] = 1;
        }
    }

    return prediction;

}

// Returns a tuple of 2 dataframes split into train/test
// Takes a dataframe and number wanted in train
tuple<vector<vector<double>>, vector<vector<double>>> splitDataframe(vector<vector<double>> dataframe, int numTrain) {

    int observations = dataframe.size();
    vector<vector<double>> train(numTrain), test(observations - numTrain);

    for (int i = 0; i < numTrain; i++) {
        train.at(i) = dataframe[i];
    }

    for (int i = numTrain; i < observations; i++) {
        test.at(i - numTrain) = dataframe[i];
    }

    return {train, test};
} 

#endif