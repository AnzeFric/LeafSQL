//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_CREATESTATEMENT_H
#define LEAFSQL_CREATESTATEMENT_H

#include <string>

// Used for creating tables and databases
class CreateDatabaseStatement {
private:
    std::string name;
public:
    CreateDatabaseStatement();
    CreateDatabaseStatement(std::string name);
    void setName(const std::string& name);
};

#endif //LEAFSQL_CREATESTATEMENT_H
