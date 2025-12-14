//
// Created by anzef on 14. 12. 2025.
//

#include "QueryParser.h"

QueryParser::QueryParser(Lexer& lexer): lexer(lexer) {}


std::vector<std::string> QueryParser::parseQuery() {
    Token token = lexer.nextToken();

    while (token.type != Token::Type::End) {

        token = lexer.nextToken();
    }
}

std::string QueryParser::toString() {
    return "";
}
