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
    static std::vector<std::vector<std::string>> getFileContentCSV(std::istream& file, char delimiter = ',');
    static void appendRowCSV(const std::string& path, const std::string& row);
};


#endif //LEAFSQL_UTILS_H