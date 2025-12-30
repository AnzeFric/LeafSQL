//
// Created by anzef on 14. 12. 2025.
//

#include "QueryParser.h"

QueryParser::QueryParser(std::string  query) : query(std::move(query)), tokens({}) {}

void parseSelectQuery (Lexer& lexer, std::vector<Token>& tokens, const QueryExecutor& queryExecutor) {
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

    queryExecutor.executeSelectQuery(selectFromStatement);
}

// TODO: parseInsertQuery
void parseInsertQuery (Lexer& lexer, std::vector<Token>& tokens, const QueryExecutor& queryExecutor) {}

// TODO: parseDeleteQuery
void parseDeleteQuery (Lexer& lexer, std::vector<Token>& tokens, const QueryExecutor& queryExecutor) {}

// TODO: parseUpdateQuery
void parseUpdateQuery (Lexer& lexer, std::vector<Token>& tokens, const QueryExecutor& queryExecutor) {}

void parseCreateQuery(Lexer& lexer, std::vector<Token>& tokens, const QueryExecutor& queryExecutor) {
    CreateStatement createStatement = CreateStatement();

    // Get the type -> TABLE | DATABASE
    Token token = lexer.nextToken();
    tokens.push_back(token);
    std::string createType = token.getValue();

    if (createType != "TABLE" && createType != "DATABASE") {
        throw std::runtime_error("Unknown type: " + createType + ". Expected: TABLE or DATABASE");
    }

    // Setting only for table, as the value is set to 'false' by default
    if (createType == "TABLE") {
        createStatement.setIsTable(true);
    }

    // Get name
    token = lexer.nextToken();
    tokens.push_back(token);

    std::string name = token.getValue();
    createStatement.setName(name);

    queryExecutor.executeCreateQuery(createStatement);
}

void QueryParser::parseQuery() {
    Lexer lexer = Lexer(this->query);

    // Keyword: SELECT | INSERT | DELETE | UPDATE | CREATE
    const Token firstKeyword = lexer.nextToken();
    tokens.push_back(firstKeyword);

    const KeywordToken keywordToken = KeywordToken(firstKeyword, firstKeyword.getValue());

    QueryExecutor queryExecutor = QueryExecutor();

    switch (keywordToken.getKeywordType()) {
        case KeywordType::SELECT:
            parseSelectQuery(lexer, tokens, queryExecutor);
            break;
        case KeywordType::INSERT:
            parseInsertQuery(lexer, tokens, queryExecutor);
            break;
        case KeywordType::DELETE:
            parseDeleteQuery(lexer, tokens, queryExecutor);
            break;
        case KeywordType::UPDATE:
            parseUpdateQuery(lexer, tokens, queryExecutor);
            break;
        case KeywordType::CREATE:
            parseCreateQuery(lexer, tokens, queryExecutor);
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
