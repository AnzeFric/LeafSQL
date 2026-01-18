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
#include <vector>
#include "../Token/Token.h"

QueryParser::QueryParser(std::string _query) : query(std::move(_query)) {}

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
    this->setDbName(token.getValue());
};

void parseSelectQuery (Lexer& lexer) {
    SelectFromStatement selectFromStatement = SelectFromStatement();

    // Columns - Loop until next Keyword -> FROM
    Token token = lexer.nextToken();

    while (token.getType() != TokenType::Keyword) {
        selectFromStatement.addField(token.getValue());
        token = lexer.nextToken();
    }

    // Table name
    selectFromStatement.setTable(lexer.nextToken().getValue());

    QueryExecutor::executeSelectQuery(selectFromStatement);
}

void parseInsertQuery (Lexer& lexer, const std::string& _dbName) {
    InsertIntoStatement insertIntoStatement = InsertIntoStatement();

    // INTO
    Token token = lexer.nextToken();

    // Table name
    insertIntoStatement.setTable(lexer.nextToken().getValue());

    // Starting bracket - '('
    lexer.nextToken();

    std::vector<std::string> columns;

    // Column - get first value
    columns.push_back(lexer.nextToken().getValue());

    // Skip comma and check if it's the end with the closing bracket: ')'
    while ((token = lexer.nextToken()).getType() != TokenType::Bracket || token.getValue() != ")") {
        // Column
        columns.push_back(lexer.nextToken().getValue());
    }

    insertIntoStatement.setColumns(columns);

    // VALUES
    lexer.nextToken();

    // Starting bracket - '('
    lexer.nextToken();

    std::vector<std::string> values;

    // Column - get first value
    values.push_back(lexer.nextToken().getValue());

    // Skip comma and check if it's the end with the closing bracket: ')'
    while ((token = lexer.nextToken()).getType() != TokenType::Bracket || token.getValue() != ")") {
        // Column
        values.push_back(lexer.nextToken().getValue());
    }

    insertIntoStatement.setValues(values);

    QueryExecutor::executeInsertQuery(insertIntoStatement, _dbName);
}

// TODO: parseDeleteQuery
void parseDeleteQuery (Lexer& lexer) {}

// TODO: parseUpdateQuery
void parseUpdateQuery (Lexer& lexer) {}

void parseTableValues(Lexer& lexer, CreateTableStatement& createTable) {
    // Starting bracket - '('
    Token token = lexer.nextToken();
    if (token.getValue() != "(") {
        throw std::runtime_error("Syntax error! Expected '(' but got: " + token.getValue());
    }

    // First column name
    token = lexer.nextToken();
    createTable.addColumn(token.getValue());

    std::vector<std::string> attributes;

    // Read attributes for the first column
    token = lexer.nextToken();

    while (token.getType() != TokenType::Bracket && token.getType() != TokenType::End) {
        if (token.getType() == TokenType::Comma) {
            // Save attributes for the previous column
            createTable.addAttribute(attributes);
            attributes.clear();

            // Next column name
            token = lexer.nextToken();
            createTable.addColumn(token.getValue());
        } else {
            // Attribute for the current column
            attributes.push_back(token.getValue());
        }

        token = lexer.nextToken();
    }

    // Attributes for the last column
    createTable.addAttribute(attributes);

    // Closing bracket - ')'
    if (token.getValue() != ")") {
        throw std::runtime_error("Syntax error! Expected ')' but got: " + token.getValue());
    }
}

void parseCreateQuery(Lexer& lexer, const std::string& _dbName) {
    // Get the type -> TABLE | DATABASE
    Token token = lexer.nextToken();
    const std::string createType = token.getValue();

    if (createType != "TABLE" && createType != "DATABASE") {
        throw std::runtime_error("Unknown type: " + createType + ". Expected: TABLE or DATABASE");
    }

    // Get name
    token = lexer.nextToken();
    const std::string name = token.getValue();

    if (createType == "TABLE") {
        CreateTableStatement createTable = CreateTableStatement();
        createTable.setName(name);

        parseTableValues(lexer, createTable);

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

    const KeywordToken keywordToken = KeywordToken(firstKeyword, firstKeyword.getValue());

    switch (keywordToken.getKeywordType()) {
        case KeywordType::SELECT:
            parseSelectQuery(lexer);
            break;
        case KeywordType::INSERT:
            parseInsertQuery(lexer, this->dbName);
            break;
        case KeywordType::DELETE:
            parseDeleteQuery(lexer);
            break;
        case KeywordType::UPDATE:
            parseUpdateQuery(lexer);
            break;
        case KeywordType::CREATE:
            parseCreateQuery(lexer, this->dbName);
            break;
        case KeywordType::USE:
            this->parseUseDatabaseQuery(lexer);
            break;
        default:
            throw std::runtime_error(std::string("SQL statement is invalid!"));
    }
}
