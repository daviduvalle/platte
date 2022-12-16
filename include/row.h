#ifndef ROW_H
#define ROW_H

#include <string>
#include <vector>

class Row
{
    public:
        Row();
        Row(std::vector<std::string> rowData);
        std::vector<std::string> Data();
    private:
        std::vector<std::string> rowData;
};

#endif