//
// Created by anzef on 25. 01. 2026.
//

#include "QueryPreparer.h"
#include "../QueryValidator/QueryValidator.h"
#include "../Shared/Globals/Globals.h"
#include "../Shared/Utils/Utils.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <sstream>

std::vector<std::string> getDefinitionFilePaths(const std::string& tableName) {
    const std::string dirPathStr = "data/" + g_activeDbName + "/" + tableName + "/";

    const std::string tableDataStr = dirPathStr + tableName + "_data.csv";
    const std::string tableColumnsStr = dirPathStr + tableName + "_columns.csv";
    const std::string tableAttributesStr = dirPathStr + tableName + "_attributes.csv";

    return std::vector {tableColumnsStr, tableAttributesStr, tableDataStr};
}

void QueryPreparer::prepareSelectQuery(const SelectFromStatement& selectFromStatement) {
    const std::string tableName = selectFromStatement.getTable();
    const std::vector<std::string> filePaths = getDefinitionFilePaths(tableName);

    // Get table columns
    const std::vector<std::string> tableColumns = Utils::getFileRowsCSV(filePaths[0]);
    std::vector<int> columnIndexes(tableColumns.size());

    // Get user requested columns
    const std::vector<std::string> userColumns = selectFromStatement.getColumns();

    // IF - User requested all columns - '*'
    // ELSE - User requested specific columns
    if (userColumns.front() == "*") {
        std::iota(columnIndexes.begin(), columnIndexes.end(), 0);
    } else {
        // Clear array from previous init with tableColumns.size()
        columnIndexes.clear();

        // Get indexes of columns that match definition
        for (int i = 0; i < tableColumns.size(); i++) {
            if (std::ranges::find(userColumns, tableColumns[i]) != userColumns.end()) {
                columnIndexes.push_back(i);
            }
        }
    }

    try {
        QueryValidator::validateSelectQuery(columnIndexes, selectFromStatement.getTable());
    } catch (const std::exception& e) {
        throw std::runtime_error("SELECT FROM TABLE '" + tableName + "': " + e.what());
    }
}

void QueryPreparer::prepareInsertQuery(InsertIntoStatement insertIntoStatement) {
    const std::string tableName = insertIntoStatement.getTable();
    const std::vector<std::string> filePaths = getDefinitionFilePaths(tableName);

    // Get table definition values
    const std::vector<std::string> tableColumns = Utils::getFileRowsCSV(filePaths[0]);
    const std::vector<std::string> tableAttributes = Utils::getFileRowsCSV(filePaths[1]);

    // Get user insert values
    std::vector<std::string> insertColumns = insertIntoStatement.getColumns();
    std::vector<std::string> insertValues = insertIntoStatement.getValues();

    for (int columnIndex = 0; columnIndex < tableColumns.size(); columnIndex++) {
        bool foundColumn = false;
        for (const auto & insertColumn : insertColumns) {
            if (tableColumns[columnIndex] == insertColumn) {
                foundColumn = true;
                break;
            }
        }

        // Column not inserted, check if it's NULL
        if (!foundColumn && tableAttributes[columnIndex].find("NULL") != std::string::npos) {
            insertColumns.push_back(tableColumns[columnIndex]);
            insertValues.push_back("NULL");
        }
    }

    try {
        const std::string& dataTablePath = filePaths[2];
        QueryValidator::validateInsertQuery(dataTablePath, tableColumns, tableAttributes, insertColumns, insertValues);
    } catch (const std::exception& e) {
        throw std::runtime_error("INSERT INTO TABLE '" + tableName + "': " + e.what());
    }
}

// TODO: Make prepare update query
void QueryPreparer::prepareUpdateQuery(UpdateStatement updateStatement) {}

void QueryPreparer::prepareDeleteQuery(DeleteFromStatement deleteFromStatement) {
    try {
        std::vector<int> deleteRowIndexes;

        const std::string tableName = deleteFromStatement.getTable();
        std::vector<Condition> conditions = deleteFromStatement.getConditions();

        const std::vector<std::string> filePaths = getDefinitionFilePaths(tableName);

        const std::vector<std::string> tableColumns = Utils::getFileRowsCSV(filePaths[0]);

        // Check that all table columns exist
        for (auto& condition : conditions) {
            const auto it = std::ranges::find(tableColumns, condition.column);

            if (it == tableColumns.end()) {
                throw std::runtime_error("Column not found: " + condition.column);
            }

            // Column exists. Get its index
            condition.columnIndex = std::distance(tableColumns.begin(), it);
        }

        const std::string& dataFilePath = filePaths[2];

        std::ifstream in(dataFilePath);

        std::string line;
        int lineIndex = 0;

        while (std::getline(in, line)) {

            std::vector<std::string> fields;

            std::stringstream ss(line);
            std::string field;

            while (std::getline(ss, field, ',')) {
                if (!field.empty() && field.front() == ' ') {
                    field.erase(0, 1);
                }
                fields.push_back(field);
            }

            bool conditionRes;
            LogicalOperator prevOperator = END;

            for (const auto& condition : conditions) {

                bool conditionValue = condition.value == fields[condition.columnIndex];

                if (prevOperator == END) {
                    conditionRes = conditionValue;
                } else if (prevOperator == AND) {
                    conditionRes = conditionRes && conditionValue;
                } else {
                    conditionRes = conditionRes || conditionValue;
                }

                prevOperator = condition.logicalOperator;
            }

            if (conditionRes) {
                deleteRowIndexes.push_back(lineIndex);
            }
            ++lineIndex;
        }

        in.close();

        deleteFromStatement.setDeleteRowIndexes(deleteRowIndexes);


        QueryValidator::validateDeleteQuery(deleteFromStatement);
    } catch (const std::exception& e) {
        throw std::runtime_error("DELETE FROM TABLE '" + deleteFromStatement.getTable() + "': " + e.what());
    }
}

void QueryPreparer::prepareCreateDatabaseQuery(const CreateDatabaseStatement& createDatabaseStatement) {
    try {
        QueryValidator::validateCreateDatabaseQuery(createDatabaseStatement);
    } catch (const std::exception& e) {
        throw std::runtime_error("CREATE DATABASE '" + createDatabaseStatement.getName() + "': " + e.what());
    }
}

void QueryPreparer::prepareCreateTableQuery(const CreateTableStatement& createTableStatement) {
    try {
        QueryValidator::validateCreateTableQuery(createTableStatement);
    } catch (const std::exception& e) {
        throw std::runtime_error("CREATE TABLE '" + createTableStatement.getName() + "': " + e.what());
    }
}

void QueryPreparer::prepareUseDatabaseQuery(const UseDatabaseStatement& useDatabaseStatement) {
    try {
        QueryValidator::validateUseDatabaseQuery(useDatabaseStatement);
    } catch (const std::exception& e) {
        throw std::runtime_error("USE DATABASE '" + useDatabaseStatement.getName() + "': " + e.what());
    }
};
