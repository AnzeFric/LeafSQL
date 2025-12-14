//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_TOKEN_H
#define LEAFSQL_TOKEN_H

#include <string>

struct Token {
    enum class Type { Keyword, Identifier, Comma, End };
    Type type;
    std::string value;
};

#endif //LEAFSQL_TOKEN_H
