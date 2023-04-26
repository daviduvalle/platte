#ifndef ML_ALGORITHM_H
#define ML_ALGORITHM_H

#include <string>
#include <vector>

class MLAlgorithm {
  public:
    virtual void train() = 0;
    virtual double predict(std::vector<double> input) = 0;
    virtual std::vector<double> getWeights() = 0;
  private:
};

#endif
