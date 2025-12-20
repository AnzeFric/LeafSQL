//
// Created by anzef on 14. 12. 2025.
//

#ifndef LEAFSQL_TOKEN_H
#define LEAFSQL_TOKEN_H

#include <string>

// Init the enum inside the Token for later importing in other files
struct Token {
    enum class Type { Keyword, Identifier, Everything, Comma, Start, End };
    Type type;
    std::string value;
};

#endif //LEAFSQL_TOKEN_H
