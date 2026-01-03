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
    CreateTableStatement(std::string _name, std::vector<std::string> _columns, std::vector<std::vector<std::string>> _attributes);
    void setName(std::string _name);
    void setColumns(std::vector<std::string> _columns);
    void setAttributes(std::vector<std::vector<std::string>> _attributes);
    void addColumn(std::string column);
    void addAttribute(std::vector<std::string> attribute);
    std::string getName();
    std::vector<std::string> getColumns();
    std::vector<std::vector<std::string>> getAttributes();
};

#endif //LEAFSQL_CREATETABLESTATEMENT_H
