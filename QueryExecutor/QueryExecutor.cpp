//
// Created by anzef on 21. 12. 2025.
//

#include "QueryExecutor.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>

void QueryExecutor::executeSelectQuery(const SelectFromStatement& selectFromStatement) {};

void QueryExecutor::executeInsertQuery(const InsertIntoStatement& insertIntoStatement) {};

void QueryExecutor::executeUpdateQuery(const UpdateStatement& updateStatement) {};

void QueryExecutor::executeDeleteQuery(const DeleteFromStatement& deleteFromStatement) {};

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

    const std::string dirPathStr = "data/" + dbName + "/" + tableName + "/";
    const std::string tableDataStr = dirPathStr + tableName + "_data.csv";
    const std::string tableDefinitionStr = dirPathStr + tableName + "_definition.csv";

    namespace fs = std::filesystem;

    fs::path dirPath(dirPathStr);
    fs::path dataPath(tableDataStr);
    fs::path definitionPath(tableDefinitionStr);

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

    std::ofstream definitionFile(definitionPath);
    if (!definitionFile.is_open()) {
        throw std::runtime_error("Failed to create table definition file: " + tableDefinitionStr);
    }

    auto columns = createTableStatement.getColumns();
    auto attributes = createTableStatement.getAttributes();

    for (int i = 0; i < columns.size(); i++) {
        std::string input = columns[i];
        for (const auto &attribute : attributes[i]) {
            input += ", " + attribute;
        }
        definitionFile << input << "\n";
    }

    definitionFile.close();

    // Create empty data file
    std::ofstream dataFile(dataPath);
    if (!dataFile.is_open()) {
        throw std::runtime_error("Failed to create table data file: " + tableDataStr);
    }

    dataFile.close();
};
