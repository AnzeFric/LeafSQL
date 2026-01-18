//
// Created by anzef on 21. 12. 2025.
//

#include "QueryExecutor.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>

void QueryExecutor::executeSelectQuery(SelectFromStatement selectFromStatement) {};

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

void QueryExecutor::executeInsertQuery(InsertIntoStatement insertIntoStatement, const std::string& dbName) {
    const std::string tableName = insertIntoStatement.getTable();
    const std::string dirPathStr = "data/" + dbName + "/" + tableName + "/";

    const std::string tableDataStr = dirPathStr + tableName + "_data.csv";
    const std::string tableColumnsStr = dirPathStr + tableName + "_columns.csv";
    const std::string tableAttributesStr = dirPathStr + tableName + "_attributes.csv";

    const std::vector<std::string> tableColumns = getFileContents(tableColumnsStr);
    const std::vector<std::string> tableAttributes = getFileContents(tableAttributesStr);

    std::ofstream dataFile(tableDataStr, std::ios::app);
    if (!dataFile.is_open()) {
        throw std::runtime_error("Failed to open table data file: " + tableDataStr);
    }

    const std::vector<std::string> insertColumns = insertIntoStatement.getColumns();
    const std::vector<std::string> insertValues = insertIntoStatement.getValues();

    std::string insertValue;
    for (int i = 0; i < tableColumns.size(); i++ ) {
        int columnAttributeIndex = -1;
        for (int j = 0; j < insertColumns.size(); j++) {
            if (insertColumns[j] == tableColumns[i]) {
                columnAttributeIndex = j;
            }
        }

        // Column value not provided - check if it can be NULL
        if (columnAttributeIndex == -1) {
            const std::string& columnAttributes = tableAttributes[i];
            if (columnAttributes.find("NULL") != std::string::npos) {
                insertValue += "NULL, ";
            } else {
                throw std::runtime_error("For NOT NULLABLE column " + tableColumns[i] + " in table: " + tableName + ", no value was provided");
            }
        } else {
            insertValue += insertValues[columnAttributeIndex] + ", ";
        }
    }

    if (insertValue.empty()) {
        throw std::runtime_error("Inserted value is empty!");
    }
    insertValue.pop_back(); // Remove " " - Space
    insertValue.pop_back(); // Remove "," - Comma

    dataFile << insertValue << "\n";

    dataFile.close();
};

void QueryExecutor::executeUpdateQuery(UpdateStatement updateStatement) {};

void QueryExecutor::executeDeleteQuery(DeleteFromStatement deleteFromStatement) {};

void QueryExecutor::executeCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {
    const std::string dbName = createDatabaseStatement.getName();
    const std::string dbPathStr = "data/" + dbName;

    namespace fs = std::filesystem;

    const fs::path dbPath = fs::path(dbPathStr);

    try {
        fs::create_directories(dbPath);
    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error(
            "Could not create database directory (on path: " + dbPathStr + "):  " + std::string(e.what())
        );
    }
};

void QueryExecutor::executeCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName) {
    const std::string tableName = createTableStatement.getName();
    auto columns = createTableStatement.getColumns();
    auto attributes = createTableStatement.getAttributes();

    const std::string dirPathStr = "data/" + dbName + "/" + tableName + "/";
    const std::string tableDataStr = dirPathStr + tableName + "_data.csv";
    const std::string tableColumnsStr = dirPathStr + tableName + "_columns.csv";
    const std::string tableAttributesStr = dirPathStr + tableName + "_attributes.csv";

    namespace fs = std::filesystem;

    fs::path dirPath(dirPathStr);
    fs::path dataPath(tableDataStr);
    fs::path columnPath(tableColumnsStr);
    fs::path attributePath(tableAttributesStr);

    // Fail if table already exists
    if (fs::exists(dirPath)) {
        throw std::runtime_error("Table already exists: " + tableName);
    }

    // Create directory
    try {
        fs::create_directories(dirPath);
    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error(
            "Could not create directory (on path: " + dirPathStr + "):  " + std::string(e.what())
        );
    }

    std::ofstream columnFile(columnPath);
    if (!columnFile.is_open()) {
        throw std::runtime_error("Failed to create table column file: " + tableColumnsStr);
    }

    for (const auto& column: columns) {
        columnFile << column << "\n";
    }
    columnFile.close();

    std::ofstream attributeFile(attributePath);
    if (!attributeFile.is_open()) {
        throw std::runtime_error("Failed to create table attribute file: " + tableAttributesStr);
    }

    for (const auto& attribute : attributes) {
        for (size_t i = 0; i < attribute.size(); i++) {
            attributeFile << attribute[i];
            if (i < attribute.size() - 1) {
                attributeFile << ", ";
            }
        }
        attributeFile << "\n";
    }
    attributeFile.close();

    // Create empty data file
    std::ofstream dataFile(dataPath);
    if (!dataFile.is_open()) {
        throw std::runtime_error("Failed to create table data file: " + tableDataStr);
    }

    dataFile.close();
};
