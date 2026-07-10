//
// Created by Uporabnik on 10. 07. 2026.
//

#ifndef LEAFSQL_USEDATABASESTATEMENT_H
#define LEAFSQL_USEDATABASESTATEMENT_H
#include <string>


class UseDatabaseStatement {
private:
    std::string name;
public:
    UseDatabaseStatement() = default;
    explicit UseDatabaseStatement(std::string _name);
    void setName(std::string _name);
    [[nodiscard]] std::string getName() const;
};



#endif //LEAFSQL_USEDATABASESTATEMENT_H
