#include <iostream>
#include <vector>
#include <string>

#include "dataset.h"
#include "linear_regression.h"

using std::vector;
using std::string;

int main() {
    Dataset dataset = Dataset("../linear_data.csv", true, false);
    LinearRegression linearRegression = LinearRegression(&dataset);
    linearRegression.train();
    for (int i = 0; i < linearRegression.getWeights().size(); i++) {
        std::cout << linearRegression.getWeights()[i] << " ";
    }
    std::cout << "\n";
//    std::vector<double> input;
//    input.emplace_back(100);
//    double pred = linearRegression.predict(input);
//    std::cout << "Prediction: " << pred << "\n";
    return 0;
}
