//
// Created by anzef on 25. 01. 2026.
//

#include "QueryValidator.h"
#include "DataType/DataType.h"

void strToUpper(std::string& str) {
    for (auto & c: str) {
        c = static_cast<char>(toupper(c));
    }
}

bool isValidValue(std::string& value, DataType::Type type) {
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

void QueryValidator::validateSelectQuery(SelectFromStatement selectFromStatement) {}

void QueryValidator::validateInsertQuery(InsertIntoStatement insertIntoStatement, const std::string& dbName) {}

void QueryValidator::validateUpdateQuery(UpdateStatement updateStatement) {}

void QueryValidator::validateDeleteQuery(DeleteFromStatement deleteFromStatement) {}

void QueryValidator::validateCreateDatabaseQuery(CreateDatabaseStatement createDatabaseStatement) {}

void QueryValidator::validateCreateTableQuery(CreateTableStatement createTableStatement, const std::string& dbName) {}
