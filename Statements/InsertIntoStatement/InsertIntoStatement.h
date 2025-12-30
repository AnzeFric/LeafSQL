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
    InsertIntoStatement();
    InsertIntoStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values);
    void setTable(const std::string& table);
    void setColumns(const std::vector<std::string>& columns);
    void setValues(const std::vector<std::string>& values);
};

#endif //LEAFSQL_INSERTINTOSTATEMENT_H
