#include <iostream>
#include "QueryParser/QueryParser.h"

int main() {
    const std::string selectQuery = "SELECT * FROM table;";
    const std::string createDBQuery = "CREATE DATABASE LeafDB;";
    const std::string useDBQuery = "USE LeafDB;";
    const std::string createTableQuery = "CREATE TABLE users (id INT PRIMARY, username TEXT UNIQUE, email TEXT UNIQUE, age NULL INT, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, is_active BOOLEAN DEFAULT TRUE);";
    const std::string insertQuery = "INSERT INTO users (id, username, email, created_at, is_active) VALUES (1, Alice, alice@example.com, NOW(), true);";

    QueryParser queryParser = QueryParser(useDBQuery);
    queryParser.parseQuery();

    queryParser.setQuery(createTableQuery);
    queryParser.parseQuery();

    queryParser.setQuery(insertQuery);
    queryParser.parseQuery();

    return 0;
}
