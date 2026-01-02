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
    void setTable(std::string table);
    void setColumns(std::vector<std::string> columns);
    void setValues(std::vector<std::string> values);
    std::string getTable();
    std::vector<std::string> getColumns();
    std::vector<std::string> getValues();
};

#endif //LEAFSQL_UPDATESTATEMENT_H
