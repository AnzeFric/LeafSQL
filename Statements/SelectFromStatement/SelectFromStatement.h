//
// Created by anzef on 20. 12. 2025.
//

#ifndef LEAFSQL_SELECTFROMSTATEMENT_H
#define LEAFSQL_SELECTFROMSTATEMENT_H

#include <string>
#include <vector>

class SelectFromStatement {
private:
    std::string table;
    std::vector<std::string> fields;
public:
    SelectFromStatement() = default;
    SelectFromStatement(std::string _table, std::vector<std::string> _fields);
    void setTable(std::string _table);
    void setFields(std::vector<std::string> _fields);
    void addField(std::string newField);
    std::string getTable();
    std::vector<std::string> getFields();
};

#endif //LEAFSQL_SELECTFROMSTATEMENT_H
