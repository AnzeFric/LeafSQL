//
// Created by anzef on 14. 12. 2025.
//

#include "QueryParser.h"

QueryParser::QueryParser(std::string  query) : query(std::move(query)), tokens({}) {}

void QueryParser::parseQuery() {
    Lexer lexer = Lexer(this->query);
    SelectFromStatement selectFromStatement = SelectFromStatement();

    // SELECT
    lexer.nextToken();
    tokens.push_back(lexer.getToken());

    // Columns - Loop until next Keyword -> FROM
    while (lexer.nextToken().type != Token::Type::Keyword) {
        selectFromStatement.setFields(lexer.getToken().value);
        tokens.push_back(lexer.getToken());
    }
    
    // FROM
    tokens.push_back(lexer.getToken());

    // Table
    selectFromStatement.setTable(lexer.nextToken().value);
    tokens.push_back(lexer.getToken());

    // TODO: Add support for the other keywords (WHERE, ORDER BY, GROUP BY, etc.)
}

void QueryParser::print() const {
    std::cout << "Query: " << query << std::endl;
    std::cout << "Parsed into : " << std::endl;
    for (const Token& token : tokens) {
        std::cout << token.value << std::endl;
    }
}
