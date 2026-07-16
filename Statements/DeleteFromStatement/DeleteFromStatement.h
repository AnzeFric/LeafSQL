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
    UNKNOWN
};

enum LogicalOperator {
    AND,
    OR,
    END // Used to mark end of the WHERE clause
};

struct Condition {
    std::string column;
    int columnIndex;
    Symbol symbol; // e.g. "=", ">", "<"
    std::string value;
    LogicalOperator logicalOperator; // "AND", "OR"
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
    static Symbol charToSymbol(const char& symbolChar);
    static LogicalOperator strToLogicalOperator(const std::string& logicalOperatorStr);
    static std::string logicalOperatorToStr(const LogicalOperator& logicalOperator);
};


#endif //LEAFSQL_DELETEFROMSTATEMENT_H
