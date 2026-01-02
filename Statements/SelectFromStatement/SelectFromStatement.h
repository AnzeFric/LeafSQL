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
    SelectFromStatement() = default;
    SelectFromStatement(std::string table, const std::vector<std::string> &fields);
    void setTable(std::string newTable);
    void setFields(std::string newField);
    std::string getTable();
    std::vector<std::string> getFields();
};

#endif //LEAFSQL_SELECTFROMSTATEMENT_H
