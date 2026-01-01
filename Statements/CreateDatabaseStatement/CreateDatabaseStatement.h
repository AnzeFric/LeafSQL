//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_CREATEDATABASESTATEMENT_H
#define LEAFSQL_CREATEDATABASESTATEMENT_H

#include <string>

class CreateDatabaseStatement {
private:
    std::string name;
public:
    CreateDatabaseStatement() = default;
    CreateDatabaseStatement(std::string name);
    void setName(const std::string& name);
};

#endif //LEAFSQL_CREATEDATABASESTATEMENT_H
