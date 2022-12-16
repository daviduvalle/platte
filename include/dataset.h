#ifndef DATASET_H
#define DATASET_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

class Dataset 
{
    public:
        Dataset(std::string filename, bool hasHeader, bool hasIndex, bool standarize);
        void readData();
        std::vector<std::string> getHeader();
        std::vector<std::vector<double>> getTrainingData();
        std::vector<double> getLabelData();
    private:
        std::vector<std::string> _header;
        std::vector<std::vector<double>> _allData;
        std::vector<std::vector<double>> _trainingData;
        std::vector<double> _labelData;
        std::string _filename;
        bool _hasHeader;
        bool _hasIndex;
        bool _standardize;
        void standardizeData();
        std::vector<double> computeMeans();
        std::vector<double> computeStdevs(std::vector<double> *means);
};

#endif