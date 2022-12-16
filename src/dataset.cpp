#include "dataset.h"

const std::string WHITESPACE = " \n\r\t\f\v";

Dataset::Dataset(std::string filename, bool hasHeader, bool hasIndex, bool standardize)
{
    _filename = filename;
    _hasHeader = hasHeader;
    _hasIndex = hasIndex;
    _standardize = standardize;
}
 
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
    std::ifstream inputFile(_filename);
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
    if (_standardize)
    {
        standardizeData();
    }

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

void Dataset::standardizeData()
{
    std::vector<double> means = computeMeans();
    std::vector<double> stdevs = computeStdevs(&means);

    int count = 0;
    for (auto row : _allData)
    {
        for (int i = 0; i < row.size()-1; i++)
        {
            row[i] = (row[i] - means[i]) / stdevs[i];
        }
        _allData[count++] = row;
    }
}

std::vector<double> Dataset::computeMeans()
{
    std::vector<double> means(_allData.at(0).size()-1, 0);
    for (auto row : _allData)
    {
        for (int i = 0; i < row.size()-1; i++)
        {
            means[i] = means[i] + row[i];
        }
    }

    int n = _allData.size();
    for (int i = 0; i < means.size(); i++) {
        means[i] = means[i] / n;
    }

    return means;
}

std::vector<double> Dataset::computeStdevs(std::vector<double> *means)
{
    std::vector<double> stdevs(_allData.at(0).size()-1, 0);
    for (auto row : _allData)
    {
        for (int i = 0; i < row.size()-1; i++)
        {
            stdevs[i] += pow(abs(row[i] - means->at(i)), 2);
        }
    }
    int n = _allData.size();
    for (int i = 0; i < stdevs.size()-1; i++) {
        stdevs[i] = sqrt(stdevs[i] / n);
    }

    return stdevs;
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
