#include <iostream>
#include <vector>
#include <float.h>
#include <math.h>

#ifndef stats_h
#define stats_h

using namespace std;

double Sum(vector<double> &vector);
double Mean(vector<double> &vector, int observations);
double Median(vector<double> &vec, int observations);
double Range(vector<double> &vector);
vector<double> Sort(vector<double> &vec, int observations);
double covar(vector<double> &vec1, vector<double> &vec2, int observations); 
double cor(vector<double> &vec1, vector<double> &vec2, int observations);
double standard_deviation(vector<double> &vec, int observations);

void print_stats(vector<double> &vector, int observations) {

    cout << "The sum is: " << Sum(vector) << endl;
    cout << "The mean is: " << Mean(vector, observations) << endl;
    cout << "The median is: " << Median(vector, observations) << endl;
    cout << "The range is: " << Range(vector) << endl;

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

// Finds the sum from the sum function and divides it by number of observations
double Median(vector<double> &vec, int observations) {

    int median_obs = observations / 2;
    double median;

    vector<double> sorted = Sort(vec, observations);

    // If even takes the mean of two middle numbers else just takes the middle
    if (observations % 2 == 0)
        median = (sorted[median_obs] + sorted[median_obs + 1]) / 2;
    else
        median = sorted[median_obs + 1];

    return median;

}

// Loops over vector and finds the min and max values before subtracting min from max
double Range(vector<double> &vector) {
    
    double min = 1000;
    double max = -1000;

    for (double i : vector) {

        if (i < min)
            min = i;
        if (i > max)
            max = i;
    }

    double range = max - min;

    return range;
}

// Returns a sorted vector
vector<double> Sort(vector<double> &vec, int observations) {

    vector<double> sorted = vec;

    for (int i = 0; i < observations; i++) {
        double current_min = sorted.at(i);
        int swap_position = i + 1;
        for (int j = i + 1; j < observations; j++) {
            if (sorted.at(j) < current_min) {
                current_min = sorted.at(j);
                swap_position = j;
            }
        }
        swap(sorted[i], sorted[swap_position]);
    }

    return sorted;

}

double covar(vector<double> &vec1, vector<double> &vec2, int observations) {

    double avg1 = Mean(vec1, observations);
    double avg2 = Mean(vec2, observations);

    for (int i = 0; i < observations; i++) {
        vec1[i] = vec1[i] - avg1;
    }

    for (int i = 0; i < observations; i++) {
        vec2[i] = vec2[i] - avg2;
    }

    vector<double> multiplied(observations);
    for (int i = 0; i < observations; i++) {
        multiplied[i] = vec1[i] * vec2[i];
    }

    double covar = Mean(multiplied, observations);

    return covar;
}

double cor(vector<double> &vec1, vector<double> &vec2, int observations) {

    double cov = covar(vec1, vec2, observations);

    double standard_deviation1 = standard_deviation(vec1, observations);
    double standard_deviation2 = standard_deviation(vec2, observations);

    double result = cov / (standard_deviation1 * standard_deviation2);

    return result;
}

// Find the standard deviation of a vector
double standard_deviation(vector<double> &vec, int observations) {

    double mean = Mean(vec, observations);

    vector<double> square_distance(observations);

    for (int i = 0; i < observations; i++) {
        square_distance[i] = pow(vec[i] - mean, 2);
    }

    mean = Mean(square_distance, observations);

    double result = sqrt(mean);

    return result;

}



#endif