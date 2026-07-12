//
// Created by anzef on 30. 12. 2025.
//

#ifndef LEAFSQL_DELETEFROMSTATEMENT_H
#define LEAFSQL_DELETEFROMSTATEMENT_H

#include <string>
#include <vector>

class DeleteFromStatement {
private:
    std::string table;
    std::vector<int> deleteRowIndexes;
public:
    DeleteFromStatement() = default;
    explicit DeleteFromStatement(std::string _table);
    void setTable(const std::string &_table);
    void setDeleteRowIndexes(const std::vector<int>& _deleteRowIndexes);
    [[nodiscard]] std::string getTable() const;
    [[nodiscard]] std::vector<int> getDeleteRowIndexes() const;
};


#endif //LEAFSQL_DELETEFROMSTATEMENT_H
