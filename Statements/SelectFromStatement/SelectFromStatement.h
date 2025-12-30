//
// Created by anzef on 20. 12. 2025.
//

#ifndef LEAFSQL_SELECTFROMSTATEMENT_H
#define LEAFSQL_SELECTFROMSTATEMENT_H

#include <string>
#include <vector>
#include <utility>

class SelectFromStatement {
private:
    std::string table;
    std::vector<std::string> fields;
public:
    SelectFromStatement();
    SelectFromStatement(std::string table, const std::vector<std::string> &fields);
    void setTable(const std::string& newTable);
    void setFields(const std::string& newField);
};

#endif //LEAFSQL_SELECTFROMSTATEMENT_H
