#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <set>

#include "ml_algorithm.h"
#include "dataset.h"

class LinearRegression : public MLAlgorithm 
{
    public:
        LinearRegression(Dataset * dataset);
        void train();
        void predict();
        static constexpr double learningRate = 0.1;
        static constexpr int BATCH_SIZE = 32;
    private:
        Dataset *_dataset;
        double computeLoss(std::vector<double> *);
        double computePrediction(int, std::vector<double> *);
        std::vector<int> computeRandomIndices();
        std::vector<double> weightsGradient(std::vector<double> *, std::vector<int> *);
        double biasGradient(std::vector<double> *, std::vector<int> *);
        void gradientDescent(std::vector<double> *, std::vector<double> *, double);
};

#endif
