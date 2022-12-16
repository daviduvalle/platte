#include <iostream>
#include <vector>
#include <string>

#include "dataset.h"
#include "linear_regression.h"

using std::vector;
using std::string;

int main() {
    Dataset dataset = Dataset("../linear_data.csv", true, false, false);
    dataset.readData();
    LinearRegression linearRegression = LinearRegression(&dataset);
    linearRegression.train();
    
    return 0;
}
