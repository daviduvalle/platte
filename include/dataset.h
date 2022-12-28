#ifndef DATASET_H
#define DATASET_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

class Dataset 
{
    public:
        Dataset(std::string filename, bool hasHeader, bool hasIndex);
        void readData();
        std::vector<std::string> getHeader();
        std::vector<std::vector<double>> getTrainingData();
        std::vector<double> getLabelData();
        std::vector<double> getMinValues();
        std::vector<double> getMaxValues();
    private:
        std::vector<std::string> _header;
        std::vector<std::vector<double>> _allData;
        std::vector<std::vector<double>> _trainingData;
        std::vector<double> _labelData;
        std::vector<double> _minValues;
        std::vector<double> _maxValues;
        std::string _filename;
        bool _hasHeader;
        bool _hasIndex;
        void normalizeData();
        void computeMinMax();
};

#endif