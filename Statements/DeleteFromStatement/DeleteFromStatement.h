//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_DELETEFROMSTATEMENT_H
#define LEAFSQL_DELETEFROMSTATEMENT_H

#include <string>

class DeleteFromStatement {
private:
    std::string table;
public:
    DeleteFromStatement() = default;
    DeleteFromStatement(std::string table);
    void setTable(std::string table);
    std::string getTable();
};


#endif //LEAFSQL_DELETEFROMSTATEMENT_H
