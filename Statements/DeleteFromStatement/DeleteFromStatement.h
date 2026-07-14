//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_DELETEFROMSTATEMENT_H
#define LEAFSQL_DELETEFROMSTATEMENT_H

#include <string>
#include <vector>

enum Symbol {
    EQUALS,
    GREATER_THAN,
    LESS_THAN,
};

struct Condition {
    std::string column;
    Symbol symbol; // e.g. "=", ">", "<"
    std::string value;
};

class DeleteFromStatement {
private:
    std::string table;
    std::vector<int> deleteRowIndexes;
    std::vector<Condition> conditions;
public:
    DeleteFromStatement() = default;
    explicit DeleteFromStatement(std::string _table);
    void setTable(const std::string &_table);
    void setDeleteRowIndexes(const std::vector<int>& _deleteRowIndexes);
    void setConditions(const std::vector<Condition>& _conditions);
    [[nodiscard]] std::string getTable() const;
    [[nodiscard]] std::vector<int> getDeleteRowIndexes() const;
    [[nodiscard]] std::vector<Condition> getConditions() const;
};


#endif //LEAFSQL_DELETEFROMSTATEMENT_H
