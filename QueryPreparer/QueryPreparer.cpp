//
// Created by anzef on 25. 01. 2026.
//

#include "QueryPreparer.h"
#include "../QueryValidator/QueryValidator.h"
#include <fstream>
#include <stdexcept>

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

void QueryPreparer::prepareSelectQuery(SelectFromStatement selectFromStatement) {}

void QueryPreparer::prepareInsertQuery(InsertIntoStatement insertIntoStatement, const std::string& dbName) {
    const std::string tableName = insertIntoStatement.getTable();
    std::vector<std::string> filePathData = getFilePathData(tableName, dbName);

    // Get table definition values
    const std::vector<std::string> tableColumns = getFileContents(filePathData[0]);
    const std::vector<std::string> tableAttributes = getFileContents(filePathData[1]);

    // Get user insert values
    const std::vector<std::string> insertColumns = insertIntoStatement.getColumns();
    const std::vector<std::string> insertValues = insertIntoStatement.getValues();

    std::fstream dataFile(filePathData[2], std::ios::out | std::ios::app);
    if (!dataFile.is_open()) {
        throw std::runtime_error("Failed to open table: " + tableName);
    }

    // TODO: Before validation fill the NULL insertColumns and insertValues tables

    QueryValidator::validateInsertQuery(dataFile, tableColumns, tableAttributes, insertColumns, insertValues);

    dataFile.close();
}

void QueryPreparer::prepareUpdateQuery(UpdateStatement updateStatement) {}
void QueryPreparer::prepareDeleteQuery(DeleteFromStatement deleteFromStatement) {}
void QueryPreparer::prepareCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {}
void QueryPreparer::prepareCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName) {}