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
    explicit CreateDatabaseStatement(std::string _name);
    void setName(std::string _name);
    std::string getName();
};

#endif //LEAFSQL_CREATEDATABASESTATEMENT_H
