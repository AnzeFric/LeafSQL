//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_UPDATESTATEMENT_H
#define LEAFSQL_UPDATESTATEMENT_H

#include <string>
#include <vector>

class UpdateStatement {
private:
    std::string table;
    std::vector<std::string> columns;
    std::vector<std::string> values;
public:
    UpdateStatement() = default;
    UpdateStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values);
    void setTable(const std::string& table);
    void setColumns(const std::vector<std::string>& columns);
    void setValues(const std::vector<std::string>& values);
};

#endif //LEAFSQL_UPDATESTATEMENT_H
