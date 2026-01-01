//
// Created by anzef on 1. 01. 2026.
//

#ifndef LEAFSQL_CREATETABLESTATEMENT_H
#define LEAFSQL_CREATETABLESTATEMENT_H

#include <string>

// TODO: Add columns and their attributes
class CreateTableStatement {
private:
    std::string name;
public:
    CreateTableStatement();
    CreateTableStatement(std::string name);
    void setName(const std::string& name);
};

#endif //LEAFSQL_CREATETABLESTATEMENT_H
