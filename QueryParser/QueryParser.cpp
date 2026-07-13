//
// Created by anzef on 14. 12. 2025.
//

#include "QueryParser.h"
#include <iostream>
#include <utility>
#include <vector>
#include "../QueryPreparer/QueryPreparer.h"
#include "../Token/KeywordToken/KeywordToken.h"
#include "../Token/Types/KeywordType.h"
#include "../Statements/SelectFromStatement/SelectFromStatement.h"
#include "../Statements/InsertIntoStatement/InsertIntoStatement.h"
#include "../Statements/CreateDatabaseStatement/CreateDatabaseStatement.h"
#include "../Statements/CreateTableStatement/CreateTableStatement.h"
#include "../Statements/UseDatabaseStatement/UseDatabaseStatement.h"
#include "../Token/Token.h"

QueryParser::QueryParser(std::string _query) : query(std::move(_query)) {}

void QueryParser::setQuery(std::string _query) {
    this->query = std::move(_query);
};

void QueryParser::parseUseDatabaseQuery(Lexer& lexer) {
    UseDatabaseStatement useDatabaseStatement = UseDatabaseStatement();

    // DB name
    Token token = lexer.nextToken();

    useDatabaseStatement.setName(token.getValue());

    QueryPreparer::prepareUseDatabaseQuery(useDatabaseStatement);
};

// TODO: Add an optional WHERE clause
void parseSelectQuery(Lexer& lexer) {
    SelectFromStatement selectFromStatement = SelectFromStatement();

    // Columns - Loop until next Keyword -> FROM
    Token token = lexer.nextToken();

    // Either * (TokenType::Everything) or the first column
    selectFromStatement.addColumn(token.getValue());

    if (token.getType() == TokenType::Everything) {
        // FROM
        lexer.nextToken();
    } else {
        // Skip the comma until FROM
        while (lexer.nextToken().getType() != TokenType::Keyword) {
            // Next column name
            token = lexer.nextToken();

            selectFromStatement.addColumn(token.getValue());
        }
    }

    // Table name
    selectFromStatement.setTable(lexer.nextToken().getValue());

    QueryPreparer::prepareSelectQuery(selectFromStatement);
}

void parseInsertQuery(Lexer& lexer) {
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

    QueryPreparer::prepareInsertQuery(insertIntoStatement);
}

// TODO: Add WHERE clause
void parseDeleteQuery(Lexer& lexer) {
    DeleteFromStatement deleteFromStatement = DeleteFromStatement();

    // FROM
    lexer.nextToken();

    // Table name
    deleteFromStatement.setTable(lexer.nextToken().getValue());

    Token token = lexer.nextToken();
    if (token.getValue() == "WHERE") {
        std::vector<Condition> conditions;

        token = lexer.nextToken();

        // Loop until end of line
        while (token.getType() != TokenType::End) {
            Condition condition = Condition();

            condition.column = token.getValue();
            condition.symbol = lexer.nextToken().getValue();
            condition.value = lexer.nextToken().getValue();

            token = lexer.nextToken();

            conditions.push_back(condition);
        }

        deleteFromStatement.setConditions(conditions);
    }

    QueryPreparer::prepareDeleteQuery(deleteFromStatement);
}

// TODO: parseUpdateQuery
void parseUpdateQuery(Lexer& lexer) {}

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

void parseCreateQuery(Lexer& lexer) {
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

        QueryPreparer::prepareCreateTableQuery(createTable);
    } else {
        CreateDatabaseStatement createDatabase = CreateDatabaseStatement();
        createDatabase.setName(name);

        QueryPreparer::prepareCreateDatabaseQuery(createDatabase);
    }
}

void QueryParser::parseQuery() const {
    Lexer lexer = Lexer(this->query);

    // Keyword: SELECT | INSERT | DELETE | UPDATE | CREATE | USE
    const Token firstKeyword = lexer.nextToken();

    const KeywordToken keywordToken = KeywordToken(firstKeyword, firstKeyword.getValue());

    switch (keywordToken.getKeywordType()) {
        case KeywordType::SELECT:
            parseSelectQuery(lexer);
            break;
        case KeywordType::INSERT:
            parseInsertQuery(lexer);
            break;
        case KeywordType::DELETE:
            parseDeleteQuery(lexer);
            break;
        case KeywordType::UPDATE:
            parseUpdateQuery(lexer);
            break;
        case KeywordType::CREATE:
            parseCreateQuery(lexer);
            break;
        case KeywordType::USE:
            parseUseDatabaseQuery(lexer);
            break;
        default:
            throw std::runtime_error("SQL statement is invalid!");
    }
};
