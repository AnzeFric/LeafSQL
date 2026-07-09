//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_INSERTINTOSTATEMENT_H
#define LEAFSQL_INSERTINTOSTATEMENT_H

#include <string>
#include <vector>

class InsertIntoStatement {
private:
    std::string table;
    std::vector<std::string> columns;
    std::vector<std::string> values;
public:
    InsertIntoStatement() = default;
    InsertIntoStatement(std::string _table, std::vector<std::string> _columns, std::vector<std::string> _values);
    void setTable(std::string _table);
    void setColumns(std::vector<std::string> _columns);
    void setValues(std::vector<std::string> _values);
    [[nodiscard]] std::string getTable() const;
    [[nodiscard]] std::vector<std::string> getColumns() const;
    [[nodiscard]] std::vector<std::string> getValues() const;
};

#endif //LEAFSQL_INSERTINTOSTATEMENT_H
