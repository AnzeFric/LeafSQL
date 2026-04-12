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
    std::vector<std::string> columns;
public:
    SelectFromStatement() = default;
    SelectFromStatement(std::string _table, std::vector<std::string> _columns);
    void setTable(std::string _table);
    void setColumns(std::vector<std::string> _columns);
    void addColumn(std::string _column);
    std::string getTable();
    std::vector<std::string> getColumns();
};

#endif //LEAFSQL_SELECTFROMSTATEMENT_H
