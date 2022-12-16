#ifndef ML_ALGORITHM_H
#define ML_ALGORITHM_H

#include <string>

class MLAlgorithm {
  public:
    virtual void train() = 0;
    virtual void predict() = 0;
  private:
};

#endif
