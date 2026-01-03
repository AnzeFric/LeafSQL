//
// Created by anzef on 14. 12. 2025.
//

#include "QueryParser.h"
#include <iostream>
#include <utility>
#include "../QueryExecutor/QueryExecutor.h"
#include "../Token/KeywordToken/KeywordToken.h"
#include "../Token/Types/KeywordType.h"
#include "../Statements/SelectFromStatement/SelectFromStatement.h"
#include "../Statements/InsertIntoStatement/InsertIntoStatement.h"
#include "../Statements/CreateDatabaseStatement/CreateDatabaseStatement.h"
#include "../Statements/CreateTableStatement/CreateTableStatement.h"

QueryParser::QueryParser(std::string _query) : query(std::move(_query)), tokens({}) {}

std::string QueryParser::getDbName() const {
    return this->dbName;
};

void QueryParser::setDbName(std::string _dbName) {
    this->dbName = std::move(_dbName);
}

void QueryParser::setQuery(std::string _query) {
    this->query = std::move(_query);
};

void QueryParser::parseUseDatabaseQuery(Lexer& lexer) {
    // Get DB name
    const Token token = lexer.nextToken();
    this->tokens.push_back(token);

    this->setDbName(token.getValue());
};

void parseSelectQuery (Lexer& lexer, std::vector<Token>& tokens) {
    SelectFromStatement selectFromStatement = SelectFromStatement();

    // Columns - Loop until next Keyword -> FROM
    while (lexer.nextToken().getType() != TokenType::Keyword) {
        selectFromStatement.addField(lexer.getToken().getValue());
        tokens.push_back(lexer.getToken());
    }

    // FROM
    tokens.push_back(lexer.getToken());

    // Table
    selectFromStatement.setTable(lexer.nextToken().getValue());
    tokens.push_back(lexer.getToken());

    QueryExecutor::executeSelectQuery(selectFromStatement);
}

// TODO: parseInsertQuery
void parseInsertQuery (Lexer& lexer, std::vector<Token>& tokens) {}

// TODO: parseDeleteQuery
void parseDeleteQuery (Lexer& lexer, std::vector<Token>& tokens) {}

// TODO: parseUpdateQuery
void parseUpdateQuery (Lexer& lexer, std::vector<Token>& tokens) {}

void parseCreateQuery(Lexer& lexer, std::vector<Token>& tokens, const std::string& _dbName) {
    // Get the type -> TABLE | DATABASE
    Token token = lexer.nextToken();
    tokens.push_back(token);
    const std::string createType = token.getValue();

    if (createType != "TABLE" && createType != "DATABASE") {
        throw std::runtime_error("Unknown type: " + createType + ". Expected: TABLE or DATABASE");
    }

    // Get name
    token = lexer.nextToken();
    tokens.push_back(token);
    const std::string name = token.getValue();

    if (createType == "TABLE") {
        CreateTableStatement createTable = CreateTableStatement();
        createTable.setName(name);

        // TODO: Parse columns and their attributes

        QueryExecutor::executeCreateTableQuery(createTable, _dbName);
    } else {
        CreateDatabaseStatement createDatabase = CreateDatabaseStatement();
        createDatabase.setName(name);

        QueryExecutor::executeCreateDatabaseQuery(createDatabase);
    }
}

void QueryParser::parseQuery() {
    Lexer lexer = Lexer(this->query);

    // Keyword: SELECT | INSERT | DELETE | UPDATE | CREATE | USE
    const Token firstKeyword = lexer.nextToken();
    tokens.push_back(firstKeyword);

    const KeywordToken keywordToken = KeywordToken(firstKeyword, firstKeyword.getValue());

    QueryExecutor queryExecutor = QueryExecutor();

    switch (keywordToken.getKeywordType()) {
        case KeywordType::SELECT:
            parseSelectQuery(lexer, tokens);
            break;
        case KeywordType::INSERT:
            parseInsertQuery(lexer, tokens);
            break;
        case KeywordType::DELETE:
            parseDeleteQuery(lexer, tokens);
            break;
        case KeywordType::UPDATE:
            parseUpdateQuery(lexer, tokens);
            break;
        case KeywordType::CREATE:
            parseCreateQuery(lexer, tokens, this->dbName);
            break;
        case KeywordType::USE:
            this->parseUseDatabaseQuery(lexer);
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
