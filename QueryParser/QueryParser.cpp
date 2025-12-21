//
// Created by anzef on 14. 12. 2025.
//

#include "QueryParser.h"

QueryParser::QueryParser(std::string  query) : query(std::move(query)), tokens({}) {}

void parseSelectQuery (Lexer& lexer, std::vector<Token>& tokens) {
    SelectFromStatement selectFromStatement = SelectFromStatement();

    // Columns - Loop until next Keyword -> FROM
    while (lexer.nextToken().getType() != TokenType::Keyword) {
        selectFromStatement.setFields(lexer.getToken().getValue());
        tokens.push_back(lexer.getToken());
    }

    // FROM
    tokens.push_back(lexer.getToken());

    // Table
    selectFromStatement.setTable(lexer.nextToken().getValue());
    tokens.push_back(lexer.getToken());

}

// TODO: parseInsertQuery
void parseInsertQuery () {}

// TODO: parseDeleteQuery
void parseDeleteQuery () {}

// TODO: parseUpdateQuery
void parseUpdateQuery () {}

void QueryParser::parseQuery() {
    Lexer lexer = Lexer(this->query);

    // Keyword: SELECT | INSERT | DELETE | UPDATE
    const Token firstKeyword = lexer.nextToken();
    tokens.push_back(firstKeyword);

    const KeywordToken keywordToken = KeywordToken(firstKeyword, firstKeyword.getValue());

    switch (keywordToken.getKeywordType()) {
        case KeywordType::SELECT:
            parseSelectQuery(lexer, tokens);
            break;
        case KeywordType::INSERT:
            parseInsertQuery();
            break;
        case KeywordType::DELETE:
            parseDeleteQuery();
            break;
        case KeywordType::UPDATE:
            parseUpdateQuery();
            break;
        default:
            throw std::runtime_error(std::string("SQL statement is invalid!"));
    }
}

void QueryParser::print() const {
    std::cout << "Query: " << query << std::endl;
    std::cout << "Parsed into : " << std::endl;
    for (const Token& token : tokens) {
        std::cout << token.getValue() << std::endl;
    }
}
