//
// Created by anzef on 11. 07. 2026.
//

#ifndef LEAFSQL_UTILS_H
#define LEAFSQL_UTILS_H

#include <vector>
#include <string>
#include <fstream>

class Utils {
private:
public:
    static std::vector<std::vector<std::string>> getFileSplitRows(const std::string& filePath, char delimiter = ',');
    static std::vector<std::string> getFileRowsCSV(const std::string& filePath);
    static void appendRowCSV(const std::string& path, const std::string& row);
    static void deleteRowCSV(const std::string& path, const int& rowIndex);
    static std::string strToUpper(const std::string& str);
};


#endif //LEAFSQL_UTILS_H