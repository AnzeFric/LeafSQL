//
// Created by anzef on 21. 12. 2025.
//

#include "QueryExecutor.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>

void QueryExecutor::executeSelectQuery(SelectFromStatement selectFromStatement) {};

void QueryExecutor::executeInsertQuery(InsertIntoStatement insertIntoStatement) {
    std::cout << "Columns: " << std::endl;
    for (const auto& column : insertIntoStatement.getColumns()) {
        std::cout << column << std::endl;
    }

    std::cout << "Values: " << std::endl;
    for (const auto& value : insertIntoStatement.getValues()) {
        std::cout << value << std::endl;
    }
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
