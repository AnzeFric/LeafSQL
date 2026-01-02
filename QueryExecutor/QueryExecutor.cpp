//
// Created by anzef on 21. 12. 2025.
//

#include "QueryExecutor.h"
#include <filesystem>
#include <stdexcept>

QueryExecutor::QueryExecutor() {}

void QueryExecutor::executeSelectQuery(const SelectFromStatement& selectFromStatement) const {};

void QueryExecutor::executeInsertQuery(const InsertIntoStatement& insertIntoStatement) const {};

void QueryExecutor::executeUpdateQuery(const UpdateStatement& updateStatement) const {};

void QueryExecutor::executeDeleteQuery(const DeleteFromStatement& deleteFromStatement) const {};

void QueryExecutor::executeCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {
    const std::string dbName = createDatabaseStatement.getName();
    const std::string dbPathStr = "data/" + dbName;

    namespace fs = std::filesystem;

    fs::path dbPath = fs::path(dbPathStr);

    try {
        fs::create_directories(dbPath);
    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error(
            "Could not create database directory (on path: " + dbPathStr + "):  " + std::string(e.what())
        );
    }
};

void QueryExecutor::executeCreateTableQuery(const CreateTableStatement& createTableStatement) const {};
