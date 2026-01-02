//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_INSERTINTOSTATEMENT_H
#define LEAFSQL_INSERTINTOSTATEMENT_H

#include <string>
#include <vector>

class InsertIntoStatement {
private:
    std::string table;
    std::vector<std::string> columns;
    std::vector<std::string> values;
public:
    InsertIntoStatement() = default;
    InsertIntoStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values);
    void setTable(std::string table);
    void setColumns(std::vector<std::string> columns);
    void setValues(std::vector<std::string> values);
    std::string getTable();
    std::vector<std::string> getColumns();
    std::vector<std::string> getValues();
};

#endif //LEAFSQL_INSERTINTOSTATEMENT_H
