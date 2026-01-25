//
// Created by anzef on 25. 01. 2026.
//

#include "QueryValidator.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "../QueryExecutor/QueryExecutor.h"
#include "DataType/DataType.h"

int getPrimaryKeyColumnIndex(const std::vector<std::string>& tableAttributes) {
    int primaryKeyIndex = -1;
    for (int i = 0; i < tableAttributes.size(); i++ ) {
        if (tableAttributes[i].find("PRIMARY")) {
            primaryKeyIndex = i;
        }
    }
    return primaryKeyIndex;
}

void strToUpper(std::string& str) {
    for (auto & c: str) {
        c = static_cast<char>(toupper(c));
    }
}

bool isValidValue(std::string value, DataType::Type type) {
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

void QueryValidator::validateSelectQuery(SelectFromStatement selectFromStatement) {}

void QueryValidator::validateInsertQuery(std::fstream& dataFile, const std::vector<std::string>& tableColumns, const std::vector<std::string>& tableAttributes, const std::vector<std::string>& insertColumns, const std::vector<std::string>& insertValues) {

    validateInputToDefinition(tableColumns, tableAttributes, insertColumns, insertValues);

    const int primaryKeyIndex = getPrimaryKeyColumnIndex(tableAttributes);
    if (primaryKeyIndex == -1) {
        throw std::runtime_error("No primary key set on table");
    }

    // Check for existence of identical primary key as we do not automatically increment
    int insertPrimaryKeyIndex = -1;
    if (!tableAttributes[primaryKeyIndex].find("AUTO")) {
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
        int insertPrimaryKey = -1;
        try {
            insertPrimaryKey = std::stoi(insertValues[insertPrimaryKeyIndex]);
        } catch (const std::exception& e) {
            std::cerr << "Provided primary key is not of type INT: " << e.what() << std::endl;
        }

        // Go through table and check if the primary key already exists
        std::string line;
        while (std::getline(dataFile, line)) {
            std::istringstream ss(line);
            std::string temp;
            int existingPrimaryKey;

            // Skip columns before primary key column
            for (int i = 0; i < primaryKeyIndex; i++) {
                ss >> temp;
            }
            ss >> existingPrimaryKey;

            if (existingPrimaryKey == insertPrimaryKey) {
                throw std::runtime_error("Primary key: " + std::to_string(insertPrimaryKey) + ", already exists.");
            }
        }
    }

    QueryExecutor::executeInsertQuery(dataFile, tableColumns, tableAttributes, insertColumns, insertValues);
}

void QueryValidator::validateUpdateQuery(UpdateStatement updateStatement) {}

void QueryValidator::validateDeleteQuery(DeleteFromStatement deleteFromStatement) {}

// TODO: Validate input
void QueryValidator::validateCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {
    QueryExecutor::executeCreateDatabaseQuery(createDatabaseStatement);
}

// TODO: Validate input
void QueryValidator::validateCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName) {
    QueryExecutor::executeCreateTableQuery(createTableStatement, dbName);
}
