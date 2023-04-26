#include "dataset.h"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

void Dataset::readData() 
{
    std::string headerLine;
    std::string token;
    if (_hasHeader) 
    {
        getline(inputFile, headerLine);
        std::stringstream sh(headerLine);
        while (getline(sh, token, ','))
        {
            _header.emplace_back(trim(token));
        }
    }

    std::string dataLine;
    while (getline(inputFile, dataLine))
    {
        std::stringstream sd(dataLine);
        std::vector<double> row;
        while (getline(sd, token, ','))
        {
            row.emplace_back(std::stof(token));
        }
        _allData.emplace_back(row);
    }   
    inputFile.close();

    // Normalize input features to avoid integer overflow
    normalizeData();

    // Split train and label data
    int lastElementIndex = _allData.at(0).size() - 1;
    for (auto row : _allData)
    {
        _labelData.emplace_back(row.at(lastElementIndex));
        std::vector<double> copyRow(row);
        copyRow.pop_back();
        _trainingData.emplace_back(copyRow);
    }
}

void Dataset::normalizeData()
{
    computeMinMax();
    int count = 0;
    for (auto row : _allData)
    {
        for (int i = 0; i < row.size()-1; i++)
        {
            row[i] = (row[i] - _minValues.at(i)) / (_maxValues.at(i) - _minValues.at(i));
        }
        _allData[count++] = row;
    }
}

void Dataset::computeMinMax()
{
    double minVal = INT_MAX, maxVal = 0;
    int cols = _allData.at(0).size() - 1;
    int rows = _allData.size();
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            minVal = std::min(minVal, _allData[j][i]);
            maxVal = std::max(maxVal, _allData[j][i]);
        }
        _minValues.emplace_back(minVal);
        _maxValues.emplace_back(maxVal);
        maxVal = 0;
        minVal = INT_MAX;
    }
}

void Dataset::deleteData() {
    _header.clear();
    _trainingData.clear();
    _labelData.clear();
    _maxValues.clear();
    _minValues.clear();
    _allData.clear();
}

void Dataset::deleteFromSource(Dataset &source) {
    source._header.clear();
    source._trainingData.clear();
    source._labelData.clear();
    source._maxValues.clear();
    source._minValues.clear();
    source._allData.clear();
}

void Dataset::copyFromSource(const Dataset &source) {
    _header = source._header;
    _trainingData = source._trainingData;
    _labelData = source._labelData;
    _maxValues = source._maxValues;
    _minValues = source._minValues;
    _allData = source._allData;
}

Dataset::~Dataset() {
    deleteData();
}

// copy ctr
Dataset::Dataset(const Dataset &source) {
    copyFromSource(source);
}

// assign operator
Dataset & Dataset::operator=(const Dataset &source) {
    if (this == &source) {
        return *this;
    }
    deleteData();
    copyFromSource(source);
    return *this;
}

// move ctr
Dataset::Dataset(Dataset &&source) {
    copyFromSource(source);
    deleteFromSource(source);
}

Dataset & Dataset::operator=(Dataset &&source) {
    if (this == &source)
    {
        return *this;
    }
    deleteData();
    copyFromSource(source);
    deleteFromSource(source);
    return *this;
}

std::vector<std::string> Dataset::getHeader() 
{
    return _header;
}

std::vector<std::vector<double>> Dataset::getTrainingData()
{
    return _trainingData;
}

std::vector<double> Dataset::getLabelData()
{
    return _labelData;
}

std::vector<double> Dataset::getMaxValues()
{
    return _maxValues;
}

std::vector<double> Dataset::getMinValues()
{
    return _minValues;
}


