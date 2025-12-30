//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_CREATESTATEMENT_H
#define LEAFSQL_CREATESTATEMENT_H

#include <string>

// Used for creating tables and databases
class CreateStatement {
private:
    std::string name;
    bool isTable = false;
public:
    CreateStatement();
    CreateStatement(std::string name, bool isTable);
    void setName(const std::string& name);
    void setIsTable(const bool& isTable);
};

#endif //LEAFSQL_CREATESTATEMENT_H
