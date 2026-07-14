//
// Created by anzef on 30. 12. 2025.
//

#include "DeleteFromStatement.h"

#include "../../Shared/Utils/Utils.h"

DeleteFromStatement::DeleteFromStatement(std::string _table): table(std::move(_table)) {
    this->deleteRowIndexes = std::vector<int>();
    this->conditions = std::vector<Condition>();
};

void DeleteFromStatement::setTable(const std::string& _table) {
    this->table = _table;
};

std::string DeleteFromStatement::getTable() const {
    return this->table;
};

void DeleteFromStatement::setDeleteRowIndexes(const std::vector<int>& _deleteRowIndexes) {
    this->deleteRowIndexes = _deleteRowIndexes;
}

std::vector<int> DeleteFromStatement::getDeleteRowIndexes() const {
    return this->deleteRowIndexes;
}

void DeleteFromStatement::setConditions(const std::vector<Condition>& _conditions) {
    this->conditions = _conditions;
}

std::vector<Condition> DeleteFromStatement::getConditions() const {
    return this->conditions;
}

Symbol DeleteFromStatement::charToSymbol(const char& symbolChar) {
    if (symbolChar == '=') {
        return  EQUALS;
    }
    if (symbolChar == '>') {
        return GREATER_THAN;
    }
    if (symbolChar == '<') {
        return LESS_THAN;
    }
    return UNKNOWN;
}

LogicalOperator DeleteFromStatement::strToLogicalOperator(const std::string& logicalOperatorStr) {
    std::string logicalOperatorUpper = Utils::strToUpper(logicalOperatorStr);

    if (logicalOperatorUpper == "AND") {
        return AND;
    }
    if (logicalOperatorUpper == "OR") {
        return OR;
    }
    return END;
}
