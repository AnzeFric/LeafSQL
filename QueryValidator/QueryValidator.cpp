//
// Created by anzef on 25. 01. 2026.
//

#include "QueryValidator.h"

#include "../QueryExecutor/QueryExecutor.h"
#include "../Shared/Utils/Utils.h"
#include "DataType/DataType.h"
#include <algorithm>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


int getPrimaryKeyColumnIndex(const std::vector<std::string>& tableAttributes) {
    int primaryKeyIndex = -1;
    for (int i = 0; i < tableAttributes.size(); i++ ) {
        if (tableAttributes[i].find("PRIMARY")) {
            primaryKeyIndex = i;
            break;
        }
    }
    return primaryKeyIndex;
}

void strToUpper(std::string& str) {
    for (auto & c: str) {
        c = static_cast<char>(toupper(c));
    }
}

bool isValidValue(std::string value, const DataType::Type type) {
    switch(type) {
        case DataType::INT:
            try {
                std::stoi(value);
                return true;
            } catch (...) {
                return false;
            }

        case DataType::TEXT:
            return true;

        case DataType::BOOLEAN:
            strToUpper(value);
            return (value == "TRUE" || value == "FALSE" || value == "1" || value == "0");

        case DataType::TIMESTAMP:
            return true; // TODO: Make format check

        default:
            return false; // Invalid type
    }
}

// Validate that the columns user provided match the data types in table definition
void validateInputToDefinition(const std::vector<std::string>& tableColumns, const std::vector<std::string>& tableAttributes, const std::vector<std::string>& insertColumns, const std::vector<std::string>& insertValues) {
    for (int insertIndex = 0; insertIndex < insertColumns.size(); insertIndex++) {
        int currentIndex = 0;
        for (; currentIndex < tableColumns.size(); currentIndex++) {
            // Find the index for both columns in the arrays
            if (insertColumns[insertIndex] == tableColumns[currentIndex]) {
                break;
            }
        }

        // Skip other checks if the value is NULL and is allowed
        if (tableAttributes[currentIndex].find("NULL") != std::string::npos && insertValues[insertIndex] == "NULL") {
            continue;
        }

        std::stringstream ss(tableAttributes[currentIndex]);
        std::string token;
        DataType::Type dataType = DataType::UNKNOWN;

        // Get the data type of the column
        while (std::getline(ss, token, ',')) {
            // Trim whitespace
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);

            // Check for data type
            if (DataType::isValid(token)) {
                dataType = DataType::toType(token);
                break;
            }
        }

        if (dataType == DataType::UNKNOWN) {
            throw std::runtime_error("Wrong data type saved in attribute table.");
        }

        if (!isValidValue(insertValues[insertIndex], dataType)) {
            throw std::runtime_error("Provided value is not the right type.");
        }
    }
}

// TODO: Add select validation
void QueryValidator::validateSelectQuery(const std::vector<int>& columnIndexes, const std::string& tableName) {
    QueryExecutor::executeSelectQuery(columnIndexes, tableName);
}

void QueryValidator::validateInsertQuery(const std::string& dataTablePath, const std::vector<std::string>& tableColumns, const std::vector<std::string>& tableAttributes, std::vector<std::string>& insertColumns, std::vector<std::string>& insertValues) {

    validateInputToDefinition(tableColumns, tableAttributes, insertColumns, insertValues);

    const int primaryKeyIndex = getPrimaryKeyColumnIndex(tableAttributes);
    if (primaryKeyIndex == -1) {
        throw std::runtime_error("No primary key set on table");
    }

    // Get table data
    const std::vector<std::vector<std::string>> dataFileContents = Utils::getFileSplitRows(dataTablePath);

    // IF - AUTO is set on PRIMARY KEY. Find the max and increment.
    // ELSE - AUTO is not set on PRIMARY KEY. Check if one was provided and check if the same one already exists.
    if (tableAttributes[primaryKeyIndex].find("AUTO") != std::string::npos) {
        long maxPrimaryKey = std::numeric_limits<long>::min(), value;

        // Go through the column containing primary keys and find the max
        for (const std::vector<std::string>& row: dataFileContents) {
            const std::string& primaryKey = row[primaryKeyIndex];
            auto [ptr, ec] = std::from_chars(primaryKey.data(), primaryKey.data() + primaryKey.size(), value);

            if (ec == std::errc{} && value > maxPrimaryKey) {
                maxPrimaryKey = value;
            }
        }

        // Increment the max PRIMARY KEY and convert it to string
        maxPrimaryKey++;
        const std::string maxPrimaryKeyStr = std::to_string(maxPrimaryKey);

        // Get PRIMARY KEY column name
        const std::string& primaryKeyColumnName = tableColumns[primaryKeyIndex];

        // Get the PRIMARY KEY index from user input
        const auto it = std::ranges::find(insertColumns, primaryKeyColumnName);

        int inputPrimaryKeyIndex = -1;
        if (it != insertColumns.end()) {
            inputPrimaryKeyIndex = std::distance(insertColumns.begin(), it);
        }

        // IF - PRIMARY KEY was provided. Overwrite it
        // ELSE - PRIMARY KEY was not provided. Add it to insertColumns and insertValues based on definition
        if (inputPrimaryKeyIndex != -1) {
            insertValues[inputPrimaryKeyIndex] = maxPrimaryKeyStr;
        } else {
            insertColumns.push_back(primaryKeyColumnName);
            insertValues.push_back(maxPrimaryKeyStr);
        }
    } else {
        int insertPrimaryKeyIndex = -1;

        // Check if primary key was provided
        for (int i = 0; i < insertColumns.size(); i++) {
            if (insertColumns[i] == tableColumns[primaryKeyIndex]) {
                insertPrimaryKeyIndex = i;
            }
        }

        if (insertPrimaryKeyIndex == -1) {
            throw std::runtime_error("No data for primary key provided");
        }

        // Check if provided primary key is of type int
        long insertPrimaryKey = -1;
        try {
            insertPrimaryKey = std::stoi(insertValues[insertPrimaryKeyIndex]);
        } catch (const std::exception& e) {
            std::cerr << "Provided primary key is not of type INT: " << e.what() << std::endl;
        }

        if (insertPrimaryKey < 0) {
            throw std::runtime_error("Primary key has to be a positive number.");
        }

        // Go through table and check if the primary key already exists
        for (auto& row: dataFileContents) {
            const int currentPrimaryKey = std::stoi(row[primaryKeyIndex]);

            if (currentPrimaryKey == insertPrimaryKey) {
                throw std::runtime_error("Primary key: " + std::to_string(insertPrimaryKey) + ", already exists.");
            }
        }
    }

    QueryExecutor::executeInsertQuery(tableColumns, tableAttributes, insertColumns, insertValues);
}

// TODO: Add update validation
void QueryValidator::validateUpdateQuery(UpdateStatement updateStatement) {}

// TODO: Add delete validation
void QueryValidator::validateDeleteQuery(DeleteFromStatement deleteFromStatement) {}

void QueryValidator::validateCreateDatabaseQuery(const CreateDatabaseStatement& createDatabaseStatement) {
    const std::string dbName = createDatabaseStatement.getName();
    if (dbName.length() < 1 || dbName.length() > 63) {
        throw std::runtime_error("Database name length is incorrect! Min length is 1 char and max length is 63 chars.");
    }

    if (std::ranges::find_if(dbName, isspace) != dbName.end()) {
        throw std::runtime_error("Database name contains not allowed whitespace! Use underscores.");
    }

    QueryExecutor::executeCreateDatabaseQuery(createDatabaseStatement);
}

// TODO: Add check for multiple PRIMARY attributes used.
void QueryValidator::validateCreateTableQuery(const CreateTableStatement& createTableStatement) {
    const std::string tableName = createTableStatement.getName();
    const auto tableAttributes = createTableStatement.getAttributes();

    if (tableName.length() < 1 || tableName.length() > 63) {
        throw std::runtime_error("Table name length is incorrect! Min length is 1 char and max length is 63 chars.");
    }

    if (std::ranges::find_if(tableName, isspace) != tableName.end()) {
        throw std::runtime_error("Table name contains not allowed whitespace! Use underscores.");
    }

    if (tableAttributes.empty()  || createTableStatement.getColumns().empty()) {
        throw std::runtime_error("No columns or attributes set for table: " + tableName);
    }

    const auto primaryKeyRow = std::ranges::find_if(tableAttributes, [](const auto& columnAttribute) {
        return std::find(columnAttribute.begin(), columnAttribute.end(), "PRIMARY") != columnAttribute.end();
    });

    if (primaryKeyRow == tableAttributes.end()) {
        throw std::runtime_error("Primary key parameter was not used on any column.");
    }

    const bool foundDataTypeINT = std::find(primaryKeyRow->begin(), primaryKeyRow->end(), "INT") != primaryKeyRow->end();

    if (!foundDataTypeINT) {
        throw std::runtime_error("Primary key parameter is not of type INT.");
    }

    QueryExecutor::executeCreateTableQuery(createTableStatement);
}

void QueryValidator::validateUseDatabaseQuery(const UseDatabaseStatement& useDatabaseStatement) {
    const std::string dbName = useDatabaseStatement.getName();

    namespace fs = std::filesystem;

    if (!fs::exists("data/" + dbName + "/")) {
        throw std::runtime_error("Database does not exist!");
    }

    QueryExecutor::executeUseDatabaseQuery(dbName);
}
