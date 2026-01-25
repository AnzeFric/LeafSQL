//
// Created by anzef on 25. 01. 2026.
//

#include "DataType.h"
#include <map>

const std::map<std::string, DataType::Type> stringToType = {
    {"INT", DataType::INT},
    {"TEXT", DataType::TEXT},
    {"BOOLEAN", DataType::BOOLEAN},
    {"TIMESTAMP", DataType::TIMESTAMP}
};

const std::map<DataType::Type, std::string> typeToString = {
    {DataType::INT, "int"},
    {DataType::TEXT, "string"},
    {DataType::BOOLEAN, "bool"},
    {DataType::TIMESTAMP, "string"},
    {DataType::UNKNOWN, "UNKNOWN"}
};

DataType::Type DataType::toType(const std::string& typeStr) {
    if (const auto it = stringToType.find(typeStr); it != stringToType.end()) {
        return it->second;
    }
    return UNKNOWN;
}

std::string DataType::toString(const Type& type) {
    if (const auto it = typeToString.find(type); it != typeToString.end()) {
        return it->second;
    }
    return "UNKNOWN";
}

bool DataType::isValid(const std::string& typeStr) {
    return stringToType.contains(typeStr);
}
