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
        Dataset(std::string filename, bool hasHeader, bool hasIndex) :
            inputFile(filename), _hasHeader(hasHeader), _hasIndex(hasIndex) {
            readData();
        }
        void readData();
        std::vector<std::string> getHeader();
        std::vector<std::vector<double>> getTrainingData();
        std::vector<double> getLabelData();
        std::vector<double> getMinValues();
        std::vector<double> getMaxValues();
        // object lifetime and operators
        ~Dataset();
        Dataset(const Dataset &source);
        Dataset &operator=(const Dataset &source);
        Dataset(Dataset &&source);
        Dataset &operator=(Dataset &&source);
    private:
        std::ifstream inputFile;
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
        // object lifetime helper methods
        void deleteData();
        void deleteFromSource(Dataset &source);
        void copyFromSource(const Dataset &source);
};
#endif