//
// Created by anzef on 25. 01. 2026.
//

#include "QueryPreparer.h"
#include "../QueryValidator/QueryValidator.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <iostream>

std::vector<std::string> getDefinitionFilePaths(const std::string& tableName, const std::string& dbName) {
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

void QueryPreparer::prepareSelectQuery(SelectFromStatement selectFromStatement, const std::string& dbName) {
    const std::string tableName = selectFromStatement.getTable();
    const std::vector<std::string> filePaths = getDefinitionFilePaths(tableName, dbName);

    // Get table columns
    std::vector<std::string> tableColumns = getFileContents(filePaths[0]);

    // User did not request all columns - '*'
    if (selectFromStatement.getColumns().front() != "*") {
        // Get user requested columns
        const std::vector<std::string> userColumns = selectFromStatement.getColumns();

        // Only keep the user requested columns that match the definition in tableColumns
        std::erase_if(tableColumns, [&userColumns](const std::string& item) {
            return std::ranges::find(userColumns, item) == userColumns.end();
        });
    }

    selectFromStatement.setColumns(tableColumns);

    try {
        QueryValidator::validateSelectQuery(selectFromStatement);
    } catch (const std::exception& e) {
        std::cerr << + "'" + tableName + "' table - select: " + e.what() << std::endl;
    }
}

void QueryPreparer::prepareInsertQuery(InsertIntoStatement insertIntoStatement, const std::string& dbName) {
    const std::string tableName = insertIntoStatement.getTable();
    const std::vector<std::string> filePaths = getDefinitionFilePaths(tableName, dbName);

    // Get table definition values
    const std::vector<std::string> tableColumns = getFileContents(filePaths[0]);
    const std::vector<std::string> tableAttributes = getFileContents(filePaths[1]);

    // Get user insert values
    std::vector<std::string> insertColumns = insertIntoStatement.getColumns();
    std::vector<std::string> insertValues = insertIntoStatement.getValues();

    std::fstream dataFile(filePaths[2], std::ios::out | std::ios::app);
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
            insertValues.push_back("NULL");
        }
    }

    try {
        QueryValidator::validateInsertQuery(dataFile, tableColumns, tableAttributes, insertColumns, insertValues);
    } catch (const std::exception& e) {
        std::cerr << + "'" + tableName + "' table - insert: " + e.what() << std::endl;
    }

    dataFile.close();
}

// TODO: Make prepare update query
void QueryPreparer::prepareUpdateQuery(UpdateStatement updateStatement) {}

// TODO: Make prepare delete query
void QueryPreparer::prepareDeleteQuery(DeleteFromStatement deleteFromStatement) {}

void QueryPreparer::prepareCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {
    try {
        QueryValidator::validateCreateDatabaseQuery(createDatabaseStatement);
    } catch (const std::exception& e) {
        std::cerr << + "'" + createDatabaseStatement.getName() + "' database - create: " + e.what() << std::endl;
    }
}

void QueryPreparer::prepareCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName) {
    try {
        QueryValidator::validateCreateTableQuery(createTableStatement, dbName);
    } catch (const std::exception& e) {
        std::cerr << + "Database: '" + dbName + "', Table: '" + createTableStatement.getName() + "' - create: " + e.what() << std::endl;
    }
}