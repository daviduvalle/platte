#include <iostream>
#include <vector>
#include <string>

#include "dataset.h"
#include "linear_regression.h"

using std::vector;
using std::string;

void runDemo(std::string filepath, double inputData)
{
    Dataset dataset = Dataset(filepath, true, false);
    LinearRegression linearRegression = LinearRegression(&dataset);
    linearRegression.train();
    std::vector<double> input;
    input.emplace_back(inputData);
    double pred = linearRegression.predict(input);
    std::cout << "Prediction of x: " << inputData << ", y : "<< pred << " \n";
}

int main() {
    std::cout << "Demo 1\n";
    runDemo("../linear_data.csv", 100);
    std::cout << "Demo 2\n";
    runDemo("../linear_data2.csv", 7);
    return 0;
}
