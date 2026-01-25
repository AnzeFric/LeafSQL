//
// Created by anzef on 25. 01. 2026.
//

#ifndef LEAFSQL_DATATYPE_H
#define LEAFSQL_DATATYPE_H

#include <string>

class DataType {
public:
    enum Type {
        INT,
        TEXT,
        BOOLEAN,
        TIMESTAMP,
        UNKNOWN
    };

    static Type toType(const std::string& typeStr);
    static std::string toString(const Type& type);
    static bool isValid(const std::string& typeStr);
};

#endif //LEAFSQL_DATATYPE_H
