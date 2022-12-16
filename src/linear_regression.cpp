#include "linear_regression.h"

LinearRegression::LinearRegression(Dataset * dataset) 
{
    _dataset = dataset;
}

void LinearRegression::train() 
{
    std::cout << "train" << "\n";
    int weightsCount = _dataset->getTrainingData()[0].size();
    // Include the bias
    std::vector<double> weights(weightsCount+1);
    weights[0] = 0.01;
    weights[1] = 0.01;
    std::cout << "weights count: " << weights.size() << "\n";
    double loss = computeLoss(&weights);
    int count = 0;
    while (loss > 0.00001)
    {
        {
            std::cout << "Iteration " << count << "\n";
            std::cout << "Previous loss: " << std::to_string(loss) << " running GD\n";
            std::cout << "Weights" << "\n";
            for (auto w : weights)
            {
                std::cout << w << " ";
            }
            std::cout << "\n";
        }
        std::vector<int> sample = computeRandomIndices();
        std::vector<double> weightsGradients = weightsGradient(&weights, &sample);
        double biasG = biasGradient(&weights, &sample);
        gradientDescent(&weights, &weightsGradients, biasG);
        loss = computeLoss(&weights);
        count++;
    }
    std::cout << "Final weights" << "\n";
    for (auto w : weights)
    {
        std::cout << w << " ";
    }
    std::cout << "\n";
}


double LinearRegression::computeLoss(std::vector<double> *weights)
{
    int totalSamples = _dataset->getLabelData().size();
    double y = 0, yHat = 0;
    double sum = 0;
    for (int i = 0; i < totalSamples; i++) 
    {
        y = _dataset->getLabelData().at(i);
        yHat = computePrediction(i, weights);
        double result = pow(yHat - y, 2);
        sum += result;
    }

    return sum / totalSamples;
}

double LinearRegression::computePrediction(int rowIndex, std::vector<double> * weights)
{
    double yHat = 0.0;
    for (int i = 0; i < weights->size()-1; i++) 
    {
        double sample = _dataset->getTrainingData().at(rowIndex).at(i);
        double weight = weights->at(i);
        yHat += sample * weight;
    }
    // Sum intercept
    yHat += weights->at(weights->size()-1);
    return yHat;
}

std::vector<int> LinearRegression::computeRandomIndices()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, _dataset->getLabelData().size()-1);
    std::vector<int> randomIndices;
    std::set<int> seen;

    while (randomIndices.size() < BATCH_SIZE)
    {
        int candidate = distrib(gen);
        if (seen.find(candidate) == seen.end())
        {
            seen.insert(candidate);
            randomIndices.emplace_back(candidate);
        }
    }

    return randomIndices;
}

std::vector<double> LinearRegression::weightsGradient(std::vector<double> *weights, std::vector<int> *samples)
{
    int totalSamples = samples->size();

    std::vector<double> gradients;
    for (int i = 0; i < weights->size()-1; i++) 
    {
        double sum = 0;
        for (int e = 0; e < totalSamples; e++) 
        {
            int sampleRowIndex = samples->at(e);
            double y = _dataset->getLabelData().at(sampleRowIndex);
            double y_pred = computePrediction(sampleRowIndex, weights);
            double difference = y - y_pred;
            double x_i = _dataset->getTrainingData().at(sampleRowIndex).at(i);
            double result = difference * x_i;
            sum += result;
        }
        double multiplier = -2.0 / totalSamples;
        double final = multiplier * sum;
        gradients.emplace_back(final);
    }

    return gradients;
}

double LinearRegression::biasGradient(std::vector<double> *weights, std::vector<int> *samples)
{
    int totalSamples = samples->size();
    float sum = 0.0;
    for (int i = 0; i < totalSamples; i++) 
    {
        int sampleIndex = samples->at(i);
        sum += _dataset->getLabelData().at(sampleIndex) - computePrediction(sampleIndex, weights);
    }
    double multiplier = -2.0 / totalSamples;
    double gradient = multiplier * sum;

    return gradient;
}

void LinearRegression::gradientDescent(std::vector<double> *weights, std::vector<double> *gradients, double bias)
{
    double learningRate = 0.0001;
    for (int i = 0; i < weights->size() - 1; i++)
    {
        (*weights)[i] = weights->at(i) - (learningRate * gradients->at(i));
    }
    (*weights)[weights->size()-1] = weights->at(weights->size()-1) - (learningRate * bias);
}

void LinearRegression::predict() 
{
    std::cout << "predict" << "\n";
}
