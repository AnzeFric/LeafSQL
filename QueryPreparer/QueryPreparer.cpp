//
// Created by anzef on 25. 01. 2026.
//

#include "QueryPreparer.h"
#include "../QueryValidator/QueryValidator.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

std::vector<std::string> getFilePathData(const std::string& tableName, const std::string& dbName) {
    const std::string dirPathStr = "data/" + dbName + "/" + tableName + "/";

    const std::string tableDataStr = dirPathStr + tableName + "_data.csv";
    const std::string tableColumnsStr = dirPathStr + tableName + "_columns.csv";
    const std::string tableAttributesStr = dirPathStr + tableName + "_attributes.csv";

    return std::vector {tableColumnsStr, tableAttributesStr, tableDataStr};
}

std::vector<std::string> getFileContents(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file (on path: " + filePath + ")");
    }

    std::string column;
    std::vector<std::string> columns;

    while (std::getline(file, column)) {
        columns.push_back(column);
    }

    file.close();

    return columns;
}

/*
 * 1. Get the metadata of the table
 * 2. Get user input
 * 3. Delete locally stored columns that the user did not request.
 *    We do this so that only existing columns can be requested.
 */
void QueryPreparer::prepareSelectQuery(SelectFromStatement selectFromStatement, const std::string& dbName) {
    const std::string tableName = selectFromStatement.getTable();
    const std::vector<std::string> filePathData = getFilePathData(tableName, dbName);

    // Get table columns, table data and user requested columns
    std::vector<std::string> tableColumns = getFileContents(filePathData[0]);
    const std::vector<std::string> tableData = getFileContents(filePathData[2]);
    std::vector<std::string> userColumns = selectFromStatement.getColumns();

    // Delete columns in tableColumns that the user did not request
    if (selectFromStatement.getColumns().front() != "*") {
        for (auto it = tableColumns.begin(); it != tableColumns.end();) {
            if (std::ranges::find(userColumns, *it) != userColumns.end()) {
                ++it;
            } else {
                it = tableColumns.erase(it);
            }
        }
        selectFromStatement.setColumns(tableColumns);
    }

    QueryValidator::validateSelectQuery(selectFromStatement);
}

void QueryPreparer::prepareInsertQuery(InsertIntoStatement insertIntoStatement, const std::string& dbName) {
    const std::string tableName = insertIntoStatement.getTable();
    const std::vector<std::string> filePathData = getFilePathData(tableName, dbName);

    // Get table definition values
    const std::vector<std::string> tableColumns = getFileContents(filePathData[0]);
    const std::vector<std::string> tableAttributes = getFileContents(filePathData[1]);

    // Get user insert values
    std::vector<std::string> insertColumns = insertIntoStatement.getColumns();
    std::vector<std::string> insertValues = insertIntoStatement.getValues();

    std::fstream dataFile(filePathData[2], std::ios::out | std::ios::app);
    if (!dataFile.is_open()) {
        throw std::runtime_error("Failed to open table: " + tableName);
    }

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
            insertValues.push_back(", NULL");
        }
    }

    QueryValidator::validateInsertQuery(dataFile, tableColumns, tableAttributes, insertColumns, insertValues);

    dataFile.close();
}

void QueryPreparer::prepareUpdateQuery(UpdateStatement updateStatement) {}
void QueryPreparer::prepareDeleteQuery(DeleteFromStatement deleteFromStatement) {}

void QueryPreparer::prepareCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {
    QueryValidator::validateCreateDatabaseQuery(createDatabaseStatement);
}

void QueryPreparer::prepareCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName) {
    QueryValidator::validateCreateTableQuery(createTableStatement, dbName);
}