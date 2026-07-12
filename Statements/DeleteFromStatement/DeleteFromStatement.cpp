//
// Created by anzef on 30. 12. 2025.
//

#include "DeleteFromStatement.h"

DeleteFromStatement::DeleteFromStatement(std::string _table):
                                    table(std::move(_table)) {};

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
