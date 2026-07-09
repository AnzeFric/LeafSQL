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
    [[nodiscard]] std::string getTable() const;
    [[nodiscard]] std::vector<std::string> getColumns() const;
};

#endif //LEAFSQL_SELECTFROMSTATEMENT_H
