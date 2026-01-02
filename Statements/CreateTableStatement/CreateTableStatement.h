//
// Created by anzef on 1. 01. 2026.
//

#ifndef LEAFSQL_CREATETABLESTATEMENT_H
#define LEAFSQL_CREATETABLESTATEMENT_H

#include <string>
#include <vector>

class CreateTableStatement {
private:
    std::string name;
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> attributes;
public:
    CreateTableStatement() = default;
    CreateTableStatement(std::string name, std::vector<std::string> columns, std::vector<std::vector<std::string>> attributes);
    void setName(const std::string& name);
    void setColumns(const std::vector<std::string>& columns);
    void setAttributes(const std::vector<std::vector<std::string>>& attributes);
    std::string getName();
    std::vector<std::string> getColumns();
    std::vector<std::vector<std::string>> getAttributes();
};

#endif //LEAFSQL_CREATETABLESTATEMENT_H
